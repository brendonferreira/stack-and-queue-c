#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
	char *prioridade;
	char *id;
	struct Nodo *prox;
} Nodo;

int inicializa_fila(Nodo **N) {
    *N = NULL;
}

Nodo * Cria_Nodo() {
    Nodo *p;
    p = (Nodo *) malloc(sizeof(Nodo));
    if(!p) {
        printf("Problema de alocacao");
        exit(0);
    }
    return p;
}

Nodo * pegar_o_ultimo_no( Nodo *aux ) {
    while(aux->prox != NULL)
        aux = aux->prox;
    return aux;
}

void insere_fim_lista(Nodo *fila) {
	Nodo *novo, *aux;
	novo = Cria_Nodo( );
	novo->id = fila->prox;
	novo->prioridade = fila->prox;
	novo->prox = NULL;
	if(!fila){
	    fila = novo;
	} else {
	    aux = pegar_o_ultimo_no( fila );
	    aux->prox = novo;
	}
}

void le_arquivo(Nodo *fila){
	FILE *arq;
	char string[1280];
	if((arq = fopen("arquivo.txt", "r")) == NULL){
    	printf("Erro ao abrir o arquivo.\n");
	}
	int i = 1;
	fgets(string, 1280, arq);
	fila->id = strtok(string,",");
    printf("%d ---> %s\n", i, fila->id);
	fila->prioridade = strtok(NULL,";");
    printf("%d ---> %c\n", i, *fila->prioridade);
    i++;
    while(fila->id != NULL && fila->prioridade != NULL){
        fila->id = strtok(NULL,",");
        printf("%d ---> %s\n", i, fila->id);
		fila->prioridade = strtok(NULL,";");
        printf("%d ---> %c\n", i,*fila->prioridade);
    	i++;
	}
    insere_fim_lista( fila );
	fclose(arq);
}

void arruma_filas( Nodo *queue_origem, Nodo *queue_destino ){
	Nodo *aux;
	aux->id = queue_origem->id;
	aux->prioridade = queue_origem->prioridade;
	insere_fim_lista(queue_destino);
	queue_destino->id = aux->id;
	queue_destino->prioridade = aux->prioridade;
	queue_origem = NULL;
	aux = NULL;
}

void posiciona_em_filas( Nodo *queue_entrada, Nodo *queue1, Nodo *queue2, Nodo *queue3 ){
	char um = "1";
	char dois = "2";
	char tres = "3";
	le_arquivo( queue_entrada );
	if( (strstr(um, queue_entrada->prioridade)) >= 0 ){
		arruma_filas( queue_entrada, queue1);
	} else if( (strstr(dois, queue_entrada->prioridade)) >= 0 ){
		arruma_filas( queue_entrada, queue2);
	} else if( (strstr(tres, queue_entrada->prioridade)) >= 0 ){
		arruma_filas( queue_entrada, queue3);
	}
}

int remove_inicio_lista(Nodo **N) {
    Nodo *aux, *anterior;
    if(*N == NULL)
        return 0;
    else {
        aux = *N;
        while(aux->prox != NULL) {
            anterior = aux;
            aux = aux->prox;
        }
        free(aux);
        anterior->prox = NULL;
    }
    return 1;
}

void imprime_fila(Nodo *queue_espera, Nodo *queue1, Nodo *queue2, Nodo *queue3 ) {
    Nodo *aux;
    if(queue_espera == NULL)
        printf("\n A fila esta vazia!!");
    else {
        for(aux = queue_espera; aux != NULL; aux = aux->prox) { 
            printf("Fila de Espera");
			printf("id: %d\n", queue_espera->id);
            printf("prio: %s\n", queue_espera->prioridade);
        }
        for( aux = queue1; aux != NULL; aux = aux->prox ){
        	printf("Fila 1");
        	printf("id: %d\n", queue1->id);
        	printf("prio: %s\n", queue1->prioridade);
		}
		for( aux = queue2; aux != NULL; aux = aux->prox ){
        	printf("Fila 2");
        	printf("id: %d\n", queue2->id);
        	printf("prio: %s\n", queue2->prioridade);
		}
		for( aux = queue3; aux != NULL; aux = aux->prox ){
        	printf("Fila 3");
        	printf("id: %d\n", queue3->id);
        	printf("prio: %s\n", queue3->prioridade);
		}
    }
}

int main(){
    Nodo *queue_espera = inicializa_fila( &queue_espera );
    Nodo *queue1 = inicializa_fila( &queue1 );
    Nodo *queue2 = inicializa_fila( &queue2 );
    Nodo *queue3 = inicializa_fila( &queue3 );
    le_arquivo(queue_espera);
//    posiciona_em_filas( queue_espera, queue1, queue2, queue3 );
//	imprime_fila( queue_espera, queue1, queue2, queue3 ); 
    return 0;
}
