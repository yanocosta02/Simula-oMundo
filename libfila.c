#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"

/*
 * Cria uma fila vazia e a retorna, se falhar retorna NULL.
 */
fila_t * cria_fila() {
    fila_t * f = (fila_t * ) malloc(sizeof(fila_t));

    if (f == NULL) {
        return NULL;
    }

    f -> ini = NULL;
    f -> atual = NULL;
    f -> fim = NULL;
    f -> tamanho = 0;
    return f;
}

/*
 * Remove todos os elementos da fila, libera espaco e devolve NULL.
 */
fila_t * destroi_fila(fila_t * f) {
    nodo_f_t * no;

    if (!fila_vazia(f)) {
        no = f -> ini;
        while (no) {
            f -> ini = no -> prox;
            free(no);
            f -> tamanho--;
            no = f -> ini;
        }
    }
    free(f);
    f = NULL;
    return NULL;
}
/*
 * Retorna 1 se a fila esta vazia e 0 caso contrario.
 */
int fila_vazia(fila_t * f) {
    return f -> tamanho == 0;
}

/*
 * Retorna o tamanho da fila, isto eh, o numero de elementos presentes nela.
 */
int tamanho_fila(fila_t * f) {
    return f -> tamanho;
}

/*
 * Insere o chave no final da fila (politica FIFO).
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int insere_fila(fila_t * f, int chave) {
    nodo_f_t * novo = (nodo_f_t * ) malloc(sizeof(nodo_f_t));

    if (novo == NULL) {
        return 0;
    }

    novo -> chave = chave;
    novo -> prox = NULL;

    if (fila_vazia(f)) {
        novo -> prox = NULL;
        f -> ini = novo;
    } else {
        novo -> prev = f -> fim;
        f -> fim -> prox = novo;
    }
    f -> fim = novo;
    f -> tamanho++;
    return 1;
}

/*
 * Remove o chave do inicio da fila (politica FIFO) e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int retira_fila(fila_t * f, int * chave) {
    nodo_f_t * no;

    if (fila_vazia(f))
        return 0;

    no = f -> ini;
    * chave = no -> chave;
    if (f -> ini == f -> fim) {
        f -> ini = NULL;
        f -> fim = NULL;
    } else {
        f -> ini = no -> prox;
        no -> prox -> prev = NULL;
    }

    free(no);
    f -> tamanho--;
    return 1;
}

/*
 * As funcoes abaixo permitem quebrar a politica FIFO da fila,
 * Permite acesso a elementos apontados pelo ponteiro 'atual'.
 * Este ponteiro pode ser inicializado e incrementado, viabilizando
 * a implementacao de um mecanismo iterador.
 */

/*
 * Inicializa o ponteiro atual para o primeiro elemento da fila.
 * Retorna 1 se a operacao foi bem sucedida e zero caso contrario.
 */
int inicializa_atual_fila(fila_t * f) {

    if (f == NULL) {
        return 0;
    }

    f -> atual = f -> ini;
    return 1;
}

/*
 * Faz o ponteiro atual apontar para o próximo nodo da fila f.
 */
void incrementa_atual_fila(fila_t * f) {

    if (f -> atual -> prox)
        f -> atual = f -> atual -> prox;
}

/*
 * Retorna em *elemento o valor contido na chave apontada pelo ponteiro atual. 
 * Se atual não for válido a função retorna zero senão retorna 1.
 */
int consulta_atual_fila(fila_t * atual, int * elemento) {
    
    if (!atual->atual){
        return 0;
    }

    * elemento = atual -> atual -> chave;
    return 1;
}

/*
 * Remove o elemento apontado por atual da fila f e o retorna em *elemento.
 * Faz o atual apontar para o sucessor do nodo removido.
 * Retorna 1 se houve sucesso e zero caso contrario.
 */
int retira_atual_fila(fila_t * f, int * elemento) {
    nodo_f_t * no, * aux;
    * elemento = f -> atual -> chave;

    if (fila_vazia(f) || !consulta_atual_fila(f, elemento)) {
        return 0;
    }
    /*Se for ter que retirar o primeiro elemento da lista*/
    if (f -> ini -> chave == * elemento) {
        no = f -> ini;
        f -> ini = no -> prox;
        if (f -> atual -> prox)
            f -> atual = f -> atual -> prox;
        else
            f -> atual = NULL; /*se tiver apenas um elemento na lista*/
    }
    /*se for ter que retirar o ultimo elemento da lista*/
    else if (f -> fim -> chave == * elemento) {
        no = f -> fim;
        f -> fim = no -> prev;
        no -> prev -> prox = NULL;
        f -> atual = f -> atual -> prev;
    } else {
        aux = f -> ini;
        while (aux -> prox && aux -> prox -> chave != * elemento)
            aux = aux -> prox;
        if (aux -> prox) {
            no = aux -> prox;
            aux -> prox = no -> prox;
            if (aux -> prox) {
                aux -> prox -> prev = aux;
            }
            f -> atual = f -> atual -> prev;
        }
    }

    free(no);
    f -> tamanho--;

    return 1;
}
