#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"
#include "libfila.h"
#include "liblef.h"
#include "libmundo.h"

int i; /* iterador a ser utilizado na funcao de destruir mundo*/

/* definir as variaveis globais aqui */
mundo_t Mundo; /* nosso mundo */
rumor_t Rumor[N_RUMORES_MUNDO]; /* vetor de rumores */
pessoa_t Pessoa[N_PESSOAS]; /* vetor de pessoas */
local_t Local[N_LOCAIS]; /* vetor de locais */
evento_t meu_evento[10000000]; /* vetor que guarda a estrutura do evento_t */
evento_cs meu_eventocs[10000000];  /* vetor que guarda a estrutura do evento de chegada e saida */
evento_dr meu_eventodr[10000000]; /* vetor que guarda a estrutura do evento de rumor */

/*funcao para gerar um numero aleatorio entre o intervalo*/
int ALEAT(int min,int max) {
    return rand()%(max-min+1) + min;
}

mundo_t cria_mundo(mundo_t Mundo){

	Mundo.TempoAtual = 0;
	Mundo.Pessoas = cria_conjunto(N_PESSOAS);
	Mundo.Locais = cria_conjunto(N_LOCAIS);
	Mundo.Rumores = cria_conjunto(N_RUMORES_MUNDO);
	Mundo.N_Pessoas = 100;
	Mundo.N_Locais = 8;
	Mundo.N_TamanhoMundo = 30;
    return Mundo;
}

rumor_t * cria_rumor(rumor_t * Rumor, int i){
    Rumor -> id_rumor = i;
    insere_conjunto(Mundo.Rumores, Rumor -> id_rumor);
    return Rumor;
}

pessoa_t * cria_pessoa(pessoa_t * Pessoa, int i){
    Pessoa -> id_pessoa = i;
    Pessoa -> extroversao = ALEAT(0,100);
    Pessoa -> paciencia = ALEAT(0,100);
    Pessoa -> idade = ALEAT(18,100);
    Pessoa -> crc = cria_subconjunto(Mundo.Rumores,ALEAT(1,5));
    insere_conjunto(Mundo.Pessoas,Pessoa->id_pessoa);
    return Pessoa;
}

local_t * cria_local(local_t * Local, int i){
    Local -> id_local = i;
    Local -> lotacao_max = ALEAT(5,30);
    Local -> publico = cria_conjunto(Local -> lotacao_max);
    Local -> fila_local = cria_fila();
    Local ->localizacao_x = ALEAT(0,N_TAMANHO_MUNDO-1);
    Local -> localizacao_y = ALEAT(0,N_TAMANHO_MUNDO-1);
    insere_conjunto(Mundo.Locais,Local -> id_local);
    return Local;
}
/* evento de entrada e saida */
evento_t * cria_evento(evento_t * evento, int tempo, int id_pessoa, int id_local, int tipo_evento){
	evento->tempo = tempo;
	evento->tipo = tipo_evento;
	evento->tamanho = sizeof(evento_cs);
	meu_eventocs[id_pessoa].id_pessoa = id_pessoa; /* guarda o id da pessoa e do local */
	meu_eventocs[id_pessoa].id_local = id_local;
	evento->dados = &meu_eventocs[id_pessoa];
	return evento;
}
/* evento de rumores */
evento_t * cria_evento_dr(evento_t * evento, int tempo, int id_pessoa, int id_local, int NRD, int tipo_evento){
    evento->tempo = tempo;
    evento->tipo = tipo_evento;
    evento->tamanho = sizeof(evento_cs);
    meu_eventodr[id_pessoa].id_pessoa = id_pessoa; /* guarda o id da pessoa e do local e o valor de NRD para criar os subconjuntos */
    meu_eventodr[id_pessoa].id_local = id_local;
    meu_eventodr[id_pessoa].NRD = NRD;
    evento->dados = &meu_eventocs[id_pessoa];
    return evento;
}
evento_t * cria_fim_do_mundo(evento_t * evento, int tempo, int tipo_evento){
    evento->tempo = tempo;
    evento->tipo = tipo_evento;
    evento->tamanho = sizeof(evento_cs);
    evento->dados = NULL; //evento simples
    return evento;

}

void destroi_mundo(){
    /*libera a memoria dos conjuntos do mundo*/
    destroi_conjunto(Mundo.Pessoas);
    destroi_conjunto(Mundo.Locais);
    destroi_conjunto(Mundo.Rumores);
    /*libera a memoria dos conjuntos das estruturas do mundo*/
    for (int i = 0; i < N_PESSOAS; i++) {
        destroi_conjunto(Pessoa[i].crc);
    }
    for (int i = 0; i < N_LOCAIS; i++) {
        destroi_conjunto(Local[i].publico);
    }
    for (int i = 0; i < N_LOCAIS; i++) {
        destroi_fila(Local[i].fila_local);
    }
}
