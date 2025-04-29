#ifndef MUNDO_H
#define MUNDO_H
#define N_TAMANHO_MUNDO 20000
#define N_RUMORES_MUNDO 30
#define N_PESSOAS 100
#define N_LOCAIS 8
#define FIM_DO_MUNDO 34944

#define CHEGADA 0
#define SAIDA 1
#define RUMOR 2
#define FIM 3

typedef struct evento_cs {
	int id_pessoa;   /* id da pessoa, o que vai identificar qual pessoa do mundo*/
	int id_local;    /* id do local, o que vai identificar qual pessoa do mundo*/
} evento_cs;

typedef struct evento_rumor{
	int id_pessoa;   /* id da pessoa, o que vai identificar qual pessoa do mundo*/
	int id_local;    /* id do local, o que vai identificar qual pessoa do mundo*/
	int NRD;    /* conjunto de tamanho NRD de rumores conhecidos pela pessoa*/
} evento_dr;

/*
 Criando uma struct rumor
*/
typedef  struct rumor {
	int id_rumor;   /* id do rumor, o que vai identificar cada rumor do mundo*/
} rumor_t;
/*
 Criando uma struct pessoa
*/
typedef  struct pessoa {
	int id_pessoa;   /* id da pessoa, o que vai identificar cada pessoa do mundo*/
	int extroversao;    /* Inteiro entre 0 e 100 que indica o grau de extroversao da pessoa */
	int paciencia; /* Inteiro entre 0 e 100 que indica a paciencia da pessoa */
	int idade;    /* Inteiro entre 18 e 100 indicando a idade em anos de uma pessoa. */
	conjunto_t * crc; /* Conjunto de rumores conhecidos pela pessoa */
} pessoa_t;

/*
 Criando uma struct pessoa
*/
typedef  struct local {
	int id_local;   /* id do local, o que vai identificar cada local no mundo*/
	int lotacao_max;    /* Numero maximo de pessoas no lugar*/
	conjunto_t * publico; /* Conjunto de pessoas presentes no local */
	fila_t * fila_local; /* fila caso o local esteja lotado */
	int localizacao_x; /* Par de inteiros (x, y) indicando uma coordenada em um plano cartesiano */
    int localizacao_y;
} local_t;

/*
 Criando uma struct mundo
*/
typedef  struct mundo {
	int TempoAtual;   /* Inteiro positivo indicando o tempo atual da simulacao */
	conjunto_t * Pessoas;
	conjunto_t * Locais;
	conjunto_t * Rumores;
	int N_Pessoas; /* Numero total de pessoas no mundo */
	int N_Locais; /* Numero total de locais no mundo */
	int N_TamanhoMundo; /* Coordenadas maximas do plano cartesiano dos locais */
} mundo_t;

/* declarar as structs */
extern mundo_t Mundo;
extern rumor_t Rumor[N_RUMORES_MUNDO]; /* vetor de rumores */
extern pessoa_t Pessoa[N_PESSOAS]; /* vetor de pessoas */
extern local_t Local[N_LOCAIS]; /* vetor de locais */
extern evento_t meu_evento[10000000]; /* guarda a estrutura do evento_t */
extern evento_cs meu_eventocs[10000000];  /* guarda a estrutura do evento de chegada e saida */
extern evento_dr meu_eventodr[10000000]; /* guarda a estrutura do evento de rumor */

int ALEAT(int inicio, int fim);

mundo_t cria_mundo(mundo_t Mundo);

rumor_t * cria_rumor(rumor_t * Rumor, int i);

pessoa_t * cria_pessoa(pessoa_t * Pessoa, int i);

local_t * cria_local(local_t * Local, int i);

evento_t * cria_evento(evento_t * evento, int tempo, int id_pessoa, int id_local, int tipo_evento);

evento_t * cria_evento_dr(evento_t * evento, int tempo, int id_pessoa, int id_local, int NRD, int tipo_evento);

evento_t * cria_fim_do_mundo(evento_t * evento, int tempo, int tipo_evento);

void destroi_mundo();

#endif
