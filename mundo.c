/* Implementacao SimulacaoMundo por Yan Oliveira da Costa */
#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"
#include "libfila.h"
#include "liblef.h"
#include "libmundo.h"
#include "math.h"
#include <time.h>
#define MAX(x, y)((x > y) ? (x) : (y)) 

int main() {
    int i, j, cont = 0, chave, id_pessoa, id_local, /*iterador para inicializar as structs*/
        TPL, aux, NRD, TDL, V, D, localdestino, pessoa_escuta, rumor_escuta; /* variaveis para calcular e representar dados na simulacao*/
    conjunto_t * subconj_nrd; /* conjunto criado na hora do rumor*/
    lef_t * lef; /*Minha lista de eventos futuros*/
    nodo_lef_t * evento_atual;
    srand(0); /* semente para gerar numeros aleatorios */

    lef = cria_lef(); /* cria a lista de eventos futuros */

    evento_t * prox_evento; //variavel para percorrer o vetor;
    evento_cs * ptr_meu_evento; //ponteiro para acessar os dados dos eventos de chegada e saida;
    evento_dr * ptr_meu_eventodr; //ponteiro para acessar os dados dos eventos de rumor;

    /*inicializar as structs(declaradas na libmundo.h) da simulacao */
    Mundo = cria_mundo(Mundo);

    for (i = 0; i < N_RUMORES_MUNDO; i++) {
        cria_rumor( & Rumor[i], i);
    }

    for (i = 0; i < N_PESSOAS; i++) {
        cria_pessoa( & Pessoa[i], i);
    }

    for (i = 0; i < N_LOCAIS; i++) {
        cria_local( & Local[i], i);
    }

    /*cria os primeiros eventos(CHEGADA) */
    while (cont < N_PESSOAS) {
        cria_evento( & meu_evento[cont], ALEAT(0, 96 * 7), cont, ALEAT(0, N_LOCAIS - 1), CHEGADA);
        adiciona_ordem_lef(lef, & meu_evento[cont]);
        cont++;
    }

    while ((prox_evento = obtem_primeiro_lef(lef))) {
        evento_atual = lef->Primeiro;
        lef->Primeiro = evento_atual->prox; /* passa para o prox da lista */
        free(evento_atual); /* libera a memoria do primeiro evento da lista */
        Mundo.TempoAtual = prox_evento -> tempo; /* guarda o tempo atual da simulacao */

        if (Mundo.TempoAtual >= FIM_DO_MUNDO) {
            cria_fim_do_mundo( & meu_evento[cont], FIM_DO_MUNDO, FIM);
            adiciona_inicio_lef(lef, & meu_evento[cont]);
            break; /* para o while */
        }
        switch (prox_evento -> tipo) {
            case CHEGADA:
                ptr_meu_evento = prox_evento -> dados;
                id_pessoa = ptr_meu_evento -> id_pessoa;
                id_local = ptr_meu_evento -> id_local;
                printf("\n%6d:CHEGA Pessoa%4d Local%4d  (%d/%d)", prox_evento -> tempo, id_pessoa, id_local, cardinalidade(Local[id_local].publico), Local[id_local].lotacao_max);
                /*quando chega no tempo de fim de mundo */
                if ((cardinalidade(Local[ptr_meu_evento -> id_local].publico)) >= (Local[ptr_meu_evento -> id_local].lotacao_max)) {
                    /*insere na fila caso ele tenha paciencia senao desiste*/
                    if ((Pessoa[id_pessoa].paciencia / 4 - tamanho_fila(Local[id_local].fila_local)) > 0) {
                        insere_fila(Local[id_local].fila_local, id_pessoa); 
                        printf(", FILA %d", tamanho_fila(Local[id_local].fila_local));
                    } else {
                        printf(", DESISTE");
                        cria_evento( & meu_evento[cont], Mundo.TempoAtual, id_pessoa, id_local, SAIDA); 
                        adiciona_ordem_lef(lef, & meu_evento[cont]);
                        cont++;
                    }
                    break; /* se o if ja satisfazer, para a execucao da chegada */
                }
                printf(", ENTRA");
                insere_conjunto(Local[id_local].publico, id_pessoa);
                aux = ALEAT(-2, 6);
                TPL = MAX(1, Pessoa[id_pessoa].paciencia / 10 + aux);
                NRD = Pessoa[id_pessoa].extroversao / 10; /* passar esse valor na funcao para criar rumor, para criar os subconjuntos do conjunto crc da pessoa*/
                if (((cardinalidade(Local[id_local].publico) && NRD) <= TPL)) {
                    cria_evento_dr( & meu_evento[cont], Mundo.TempoAtual + ALEAT(0, TPL), id_pessoa, id_local, NRD, RUMOR); /* cria o evento de rumor antes de sair do local*/
                    adiciona_ordem_lef(lef, & meu_evento[cont]);
                    cont++;
                }
                cria_evento( & meu_evento[cont], Mundo.TempoAtual + TPL, id_pessoa, id_local, SAIDA); /*soma o tempo atual com o tempo de permanencia e cria o evento de saida*/
                adiciona_ordem_lef(lef, & meu_evento[cont]);
                cont++;
            break;

            case SAIDA:
                ptr_meu_evento = prox_evento -> dados;
                id_pessoa = ptr_meu_evento -> id_pessoa;
                id_local = ptr_meu_evento -> id_local;
                printf("\n%6d:SAIDA Pessoa%4d Local%4d  (%d/%d)", prox_evento -> tempo, id_pessoa, id_local, cardinalidade(Local[id_local].publico), Local[id_local].lotacao_max);
                retira_conjunto(Local[id_local].publico, ptr_meu_evento -> id_pessoa); /*retira a pessoa do local*/
                /*caso houver pessoas na fila, quando sair alguem do local, ele vai inserir essa pessoa prioritariamente*/
                if (!fila_vazia(Local[id_local].fila_local) && cardinalidade(Local[id_local].publico) < Local[id_local].lotacao_max) {
                    printf(", REMOVE FILA Pessoa %d", Local[id_local].fila_local -> ini -> chave);
                    cria_evento( & meu_evento[cont], Mundo.TempoAtual, Local[id_local].fila_local -> ini -> chave, id_local, CHEGADA);
                    adiciona_inicio_lef(lef, & meu_evento[cont]);
                    retira_fila(Local[id_local].fila_local, & chave);
                    cont++;
                } else {
                    localdestino = ALEAT(0, N_LOCAIS - 1);
                    V = 100 - MAX(0, Pessoa[id_pessoa].idade - 40);
                    D = sqrt(pow(Local[localdestino].localizacao_x - Local[id_local].localizacao_x, 2) + pow(Local[localdestino].localizacao_y - Local[id_local].localizacao_y, 2));
                    TDL = D / V;
                    cria_evento( & meu_evento[cont], Mundo.TempoAtual + TDL / 15, id_pessoa, localdestino, CHEGADA); /*cria evento de chegada a outro destino */
                    adiciona_ordem_lef(lef, & meu_evento[cont]);
                    cont++;
                }
            break;

            case RUMOR:
                ptr_meu_eventodr = prox_evento -> dados;
            	id_pessoa = ptr_meu_eventodr -> id_pessoa;
            	id_local = ptr_meu_eventodr -> id_local;
            	NRD = ptr_meu_eventodr -> NRD;
            	subconj_nrd = cria_subconjunto(Pessoa[id_pessoa].crc, NRD);
            	/* percorrer as pessoas e verificar se ela ja conhece o rumor_escuta, caso passe pelo if de extroversao*/
            	printf("\n%6d:RUMOR Pessoa%4d Local%4d ", prox_evento -> tempo, id_pessoa, id_local);
            	for (i = 0; i < cardinalidade(Local[id_local].publico); i++) {
                	pessoa_escuta = Local[id_local].publico -> v[i];
                	if (ALEAT(0, 100) < Pessoa[pessoa_escuta].extroversao) {
                    	/* percorre o subconjunto de rumores conhecidos pela pessoa de origem */
                    	for (j = 0; j < cardinalidade(subconj_nrd); j++) {
                        	rumor_escuta = subconj_nrd -> v[j];
                        	if (!pertence(Pessoa[pessoa_escuta].crc, rumor_escuta)) {
                            	printf("(P%d:R%d) ", pessoa_escuta, rumor_escuta);
                            	if ((insere_conjunto(Pessoa[pessoa_escuta].crc, rumor_escuta) == 1)) { /* se ele tiver espaco em seu conjunto, o rumor passa nesse if */
                                	retira_conjunto(subconj_nrd, rumor_escuta);
                                	break; /* para o for, para mudar o valor de i, para que uma pessoa nao escute mais de 1 rumor*/
                            	} else {
                                	redimensiona(Pessoa[pessoa_escuta].crc); /*redimensiona o crc caso não tenha tamanho para receber o rumor*/
                                	insere_conjunto(Pessoa[pessoa_escuta].crc, rumor_escuta);
                                	retira_conjunto(subconj_nrd, rumor_escuta);
                                	break;
                            	}
                        	}
                    	}
                	}
            	}
            	destroi_conjunto(subconj_nrd); /* destroi o subconjunto NRD criado */
            break;

            case FIM:
            /*CHEGAMOS AO FIM DA SIMULACAO*/
            break;
        }
    }
    destroi_mundo(); /*destroi a memoria alocada ao mundo */
    destroi_lef(lef); /* destroi a lef */
    /* Para nao haver vazamentos de memoria */
}
