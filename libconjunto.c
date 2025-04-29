#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"

/*
 * Cria um conjunto vazio e o retorna, se falhar retorna NULL.
 * max eh o tamanho maximo do conjunto, isto eh, o tamanho maximo do vetor
 */
conjunto_t * cria_conjunto(int max) {
    conjunto_t * c = (conjunto_t * ) malloc(sizeof(conjunto_t));
    if (c == NULL) {
      return NULL;
    }
    c -> max = max;
    c -> card = 0;
    c -> ptr = 0;
    c -> v = (int * ) malloc(max * sizeof(int));
    return c;
}

/*
 * Remove todos os elementos do conjunto, libera espaco e devolve NULL.
 */
conjunto_t * destroi_conjunto(conjunto_t * c) {
    free(c -> v);
    c -> v = NULL;
    free(c);
    return NULL;
}

/*
 * Retorna 1 se o conjunto esta vazio e 0 caso contrario.
 */
int conjunto_vazio(conjunto_t * c) {
    return c -> card == 0;
}

/*
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
 */
int cardinalidade(conjunto_t * c) {
    return c -> card;
}

/*
 * Insere o elemento no conjunto, garante que nao existam repeticoes.
 * Retorna 1 se a operacao foi bem sucedida, 0 se tenta inserir elemento existente,
 * e retorna -1 em caso de falha por falta de espaco.
 */
int insere_conjunto(conjunto_t * c, int elemento) {

    if (pertence(c, elemento))
        return 0;

    if (cardinalidade(c) < c -> max) {
        c -> v[cardinalidade(c)] = elemento;
        c -> card++;
        return 1;
    }
    return -1;
}

/*
 * Remove o elemento elemento do conjunto caso ele exista e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
 */
int retira_conjunto(conjunto_t * c, int elemento) {
    int i;

    if (!pertence(c, elemento))
        return 0;

    /*Primeiro ele acha o elemento a ser retirado*/
    for (i = 0; i < cardinalidade(c) && c -> v[i] != elemento; i++);
    /*depois ele organiza novamente o vetor para que nao haja posicao vazia*/
    for (i = i + 1; i < cardinalidade(c); i++) {
        c -> v[i - 1] = c -> v[i];
    }
    c -> card--;
    return 1;
}

/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
 */
int pertence(conjunto_t * c, int elemento) {
    int i;

    for (i = 0; i < cardinalidade(c); i++) {
        if (elemento == c -> v[i])
            return 1;
    }
    return 0;
}

/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
 */
int contido(conjunto_t * c1, conjunto_t * c2) {
    int i, aux = 0;

    for (i = 0; i < cardinalidade(c1); i++) {
        if (pertence(c2, c1 -> v[i])) {
            aux++;
        }
    }

    if (aux == cardinalidade(c1)) {
        return 1;
    }

    return 0;
}

/*
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
 */
int sao_iguais(conjunto_t * c1, conjunto_t * c2) {
    int i, auxcard = 0;

    for (i = 0; i < cardinalidade(c1); i++) {
        if (pertence(c2, c1 -> v[i])) {
            auxcard++;
        }
    }

    if (auxcard == cardinalidade(c2))
        return 1;

    return 0;
}

/*
 * Retorna o endereco do conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna 0 se a operacao falhou.
 */
conjunto_t * cria_diferenca(conjunto_t * c1, conjunto_t * c2) {
    int i, aux = 0;
    conjunto_t * dif;
    if (c1 == NULL || c2 == NULL)
        return 0;

    for (i = 0; i < cardinalidade(c1); i++) {
        if (!pertence(c2, c1 -> v[i]))
            aux++;
    }
    /*aloca a memoria de acordo com o numero de diferencas que encontrou*/
   if(!(dif = cria_conjunto(aux)))
        return NULL;

    for (i = 0; i < cardinalidade(c1); i++) {
        if (!pertence(c2, c1 -> v[i]))
            insere_conjunto(dif, c1 -> v[i]);
    }
    return dif;
}

/*
 * Retorna o endereco do conjunto interseccao entre os conjuntos c1 e c2.
 * Retorna 0 se a operacao falhou.
 */
conjunto_t * cria_interseccao(conjunto_t * c1, conjunto_t * c2) {
    int i, r = 0; /* r contara as repeticoes*/
    conjunto_t * intersec;
    if (c1 == NULL || c2 == NULL)
        return 0;

    for (i = 0; i < cardinalidade(c1); i++) {
        if (pertence(c2, c1 -> v[i]))
            r++;
    }
    /*aloca a memoria de acordo com o numero de repeticoes*/
   if(!(intersec = cria_conjunto(r)))
        return NULL;

    for (i = 0; i < cardinalidade(c1); i++) {
        if (pertence(c2, c1 -> v[i]))
            insere_conjunto(intersec, c1 -> v[i]);
    }

    return intersec;
}

/*
 * Retorna o endereco do conjunto uniao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
conjunto_t * cria_uniao(conjunto_t * c1, conjunto_t * c2) {
    int i, auxcard, r = 0;
    conjunto_t * uniao;
    if (c1 == NULL || c2 == NULL)
        return NULL;

    for (i = 0; i < cardinalidade(c1); i++) {
        if (pertence(c2, c1 -> v[i]))
            r++;
    }
    /*faz o calculo para alocar a memoria tirando os repetidos*/
    auxcard = (cardinalidade(c1) + cardinalidade(c2)) - r;
    if(!(uniao = cria_conjunto(auxcard)))
        return NULL;
    
    for (i = 0; i < cardinalidade(c1); i++)
        insere_conjunto(uniao, c1 -> v[i]);
    for (i = 0; i < cardinalidade(c2); i++)
        insere_conjunto(uniao, c2 -> v[i]);

    return uniao;
}

/*
 * Retorna uma copia do conjunto c e 0 caso nao seja possivel.
 */
conjunto_t * cria_copia(conjunto_t * c) {
    int i;
    conjunto_t * copia;
    if (c == NULL)
        return 0;
    /*aloca a memoria com o mesmo max do conjunto original*/
    if(!(copia = cria_conjunto(c -> max)))
        return NULL;

    for (i = 0; i < cardinalidade(c); i++)
        insere_conjunto(copia, c -> v[i]);

    return copia;
}

/*
 * Cria um subconjunto com elementos aleatorios do conjunto c.
 * Se o conjunto for vazio, retorna um subconjunto vazio.
 * Se o n >= cardinalidade (c) entao retorna o proprio conjunto c.
 * Supoe que a funcao srand () tenha sido chamada antes.
 */
conjunto_t * cria_subconjunto(conjunto_t * c, int n) {
    int i, sorteia;
    conjunto_t * subconjunto;
    if (c == NULL)
        return NULL;
    /* se o conjunto for vazio */
    if (cardinalidade(c) == 0) {
        if(!(subconjunto = cria_conjunto(cardinalidade(c))))
            return NULL;

        return subconjunto;
    }
    /* se o n recebido for maior ou igual a cardinalidade de c */ 
    else if (n > cardinalidade(c)) {
        if(!(subconjunto = cria_conjunto(cardinalidade(c))))
            return NULL;

        for (i = 0; i < cardinalidade(c); i++) {
            insere_conjunto(subconjunto, c -> v[i]);
        }
        return subconjunto;
    }
    /* cria um subconjunto de tamanho n */  
    else {
        if(!(subconjunto = cria_conjunto(n)))
            return NULL;

        while (cardinalidade(subconjunto) < n) {
            /* So para quando a cardinalidade do subconjunto = n */
            sorteia = rand() % cardinalidade(c); /*sorteia uma posicao do conjunto pra inserir no subconjunto*/
            insere_conjunto(subconjunto, c -> v[sorteia]);
        }
        return subconjunto;
    }
}

/*
 * Imprime os elementos do conjunto sempre em ordem crescente,
 * mesmo que a estrutura interna nao garanta isso.
 */
void imprime(conjunto_t * c) {
    int aux, i, j;

    if (c != NULL) {
        printf("\n{ ");
        for (i = 0; i < cardinalidade(c); i++) {
            for (j = i + 1; j < cardinalidade(c); j++) {
                if (c -> v[i] > c -> v[j]) {
                    /*guarda o valor em aux para ir substituindo e imprimir o vetor ordenado*/
                    aux = c -> v[i];
                    c -> v[i] = c -> v[j];
                    c -> v[j] = aux;
                }
            }

            printf("%d ", c -> v[i]);
        }
    }
    printf("}");
}

/*
 * Retorna 1 se conseguiu dobrar o tamanho max do conjunto e 0 caso contrario.
 */
int redimensiona(conjunto_t * c) {
    if (c -> max >= 1) {
        c -> max = c -> max * 2; /*altera o valor de c->max para o seu dobro*/
        c -> v = realloc(c -> v, c -> max * sizeof(int)); /*faz o realloc para redimensionar a memoria alocada*/
        return 1;
    }

    return 0;
}

/*
 * As funcoes abaixo permitem acessar elementos apontados pelo ponteiro 'ptr'.
 * Este ponteiro pode ser inicializado e incrementado, viabilizando
 * a implementacao de um mecanismo iterador.
 */

/*
 * Inicializa o contador que sera usado na funcao incrementar_iterador 
 */
void iniciar_iterador(conjunto_t * c) {
    c -> ptr = 1; /*inicia o iterador com o indice 1*/
}

/*
 * Incrementa iterador e retorna o elemento apontado. Retorna 0 se acabou conjunto 
 */
int incrementar_iterador(conjunto_t * c, int * elemento) {
    /*enquanto o iterador apontar para uma posicao do conjunto, realiza o if*/
    if (c -> ptr < cardinalidade(c)) {
        * elemento = c -> v[c -> ptr];
        c -> ptr++;
        return *elemento;
    }
    return 0;
}

/*
 * Escolhe um elemento qualquer do conjunto para ser removido e o remove.
 * Nao faz teste se conjunto eh vazio, deixa para main fazer isso       
 */
int retirar_um_elemento(conjunto_t * c) {
    int sorteia;

    if (c == NULL)
        return 0;

    sorteia = rand() % cardinalidade(c); /*sorteia um elemento a ser retirado*/
    retira_conjunto(c, c -> v[sorteia]);

    return 1;
}
