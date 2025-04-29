#include <stdio.h>
#include <stdlib.h>
#include "liblef.h"

/* 
 * Cria uma LEF vazia 
*/
lef_t * cria_lef (){
    lef_t * l = (lef_t * ) malloc(sizeof(lef_t));

    if(l == NULL)
    	return NULL;

    l -> Primeiro = NULL;
    return l;
}

/* 
 * Destroi a LEF, sempre retorna NULL. 
 * Note que nao eh possivel desalocar estruturas dentro de evento->dados se existirem 
*/ 
lef_t * destroi_lef (lef_t *l){
    nodo_lef_t * no;

    no = l -> Primeiro;
    while (no) {
        l -> Primeiro = no -> prox;
        free(no);
        no = l -> Primeiro;
    }
    free(l);
    return NULL;
}
/* 
 * Adiciona um evento na primeira posicao da LEF. Uma nova copia
 * da estrutura evento sera feita .
*/ 
int adiciona_inicio_lef (lef_t *l, evento_t *evento){
    nodo_lef_t * novo = (nodo_lef_t * ) malloc(sizeof(nodo_lef_t));

    if (novo == NULL) {
        return 0;
    }

    novo -> prox = l -> Primeiro;
    novo -> evento = evento;
    l -> Primeiro = novo;

    return 1;
}
/* 
 * Adiciona um evento de acordo com o valor evento->tempo na LEF. 
 * Uma nova copia da estrutura evento sera feita 
*/
void adiciona_ordem_lef(lef_t * l, evento_t * evento) {
    nodo_lef_t * aux, * novo = (nodo_lef_t * ) malloc(sizeof(nodo_lef_t));

    novo -> evento = evento;
    novo -> prox = NULL;
    /*Se a lista estiver vazia*/
    if (l->Primeiro == NULL ) {
        novo -> prox = NULL;
        l -> Primeiro = novo;
    }
    /*Se for ter que inserir o primeiro elemento da lista*/
    else if (l -> Primeiro -> evento -> tempo >= novo -> evento -> tempo) {
        novo -> prox = l -> Primeiro;
        l -> Primeiro = novo;
    } else { /*se for inserir no meio ou no fim da lista */
        aux = l -> Primeiro; /*aux vai percorrer a lista*/
        while (aux -> prox && novo -> evento -> tempo >= aux -> prox -> evento -> tempo)
            aux = aux -> prox;
        novo -> prox = aux -> prox;
        aux -> prox = novo;
    }

}

/* 
 * Retorna o primeiro evento da LEF. A responsabilidade por desalocar
 * a memoria associado eh de quem chama a funcao 
*/
evento_t * obtem_primeiro_lef (lef_t *l){
    evento_t * evento;

    if(l->Primeiro == NULL)
        return NULL;

    evento = l->Primeiro->evento;
    /* quem chama a funcao vai passar para o proximo e liberar a memoria do evento atual */
    return evento;
}
