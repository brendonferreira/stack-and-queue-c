#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Bloco {
    struct Bloco *prox;
} Nodo;

typedef struct FILA {
	int prioridade;
	char *id;
	Nodo bloco; 
} Fila;

void inicializa_fila(Nodo **N) {
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

Nodo * pegar_o_ultimo_no( Nodo * aux ) {
    while(aux->prox != NULL)
        aux = aux->prox;
    return aux;
}

void insere_fila(Nodo **N) {
	Fila fila;
	Nodo *novo, * aux;
	novo = Cria_Nodo( );
	novo->fila = fila;
	novo->prox = NULL;
	if(*N == NULL)
	    *N = novo;
	else {
	    aux = pegar_o_ultimo_no( *N );
	    aux->prox = novo;
	}
}

void le_arquivo_e_insere(Nodo **N){
	Fila fila;
	FILE *arq;
	if((arq = fopen("arquivo.txt", "r")) == NULL){
    	printf("Erro ao abrir o arquivo.\n");
	}
	fseek(arq,0,SEEK_SET);
	char string[6400] = fread(string, 6400,1, arq);
	fila.id = strtok(string,"*,*");
    fila.prioridade = strtok(NULL,"*;*");
        while (fila.id != NULL && fila.prioridade != NULL){
                printf("The id is:  %s\n", fila.id);
                fila.id = strtok(NULL," ,");
                printf("The prio is:  %s\n", fila.prioridade);
                fila.prioridade = strtok(NULL," ;");
        }
	fclose(arq);
}

void posiciona_em_filas( Nodo **N ){
	Fila fila;
	char um = "1";
	char dois = "2";
	char tres = "3";
	le_arquivo_e_insere( N );
	if( strstr(um, fila.prioridade) ){
		insere_fila( N );
		remove_fila( N );
	} else if( strstr(dois, fila.prioridade)){
		insere_fila( N );
		remove_fila( N );
	} else if( strstr(tres, fila.prioridade)){
		insere_fila( N );
		remove_fila( N );
	}
}

int remove_fila(Nodo **N) {
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

void imprime_fila(Nodo *N) {
    Nodo *aux;
    Fila fila;
    if(N == NULL)
        printf("\n A lista esta vazia!!");
    else {
        for(aux = N; aux != NULL; aux = aux->prox) { 
            printf("id: %d\n", fila.id);
            printf("prio: %s\n", fila.prioridade);
        }
    }
} 

int main(){
    Nodo *QueueZero = NULL;
    Nodo *QueueOne = NULL;
    Nodo *QueueTwo = NULL;
    Nodo *QueueThree = NULL;
    int menu;
	inicializa_fila(&QueueZero);
	le_arquivo_e_insere(&QueueZero);
    imprime_fila(&QueueZero);
	    do {
	        printf("\n1. Inserir novas requisicoes\n");
	        printf("\n2. Mostrar fila principal\n");
	        printf("\n3. Mostrar fila 1\n");
	        printf("\n4. Mostrar fila 2\n");
	        printf("\n5. Mostrar fila 3\n");
	        printf("\n6. Sair\n");
			scanf("%d", &menu);
	        switch(menu) {
	            case 1:
	            	//função para inserir
	                break;
	            case 2:
	            	//printa fila 0
					break;
	            case 3: 
	                //printa fila 1
	                break;
	            case 4: 
	            	//printa fila 2
	                break;
	            case 5: 
	                //print fila 3
	                break;
	            case 6: 
	                printf("\n\n\nSaindo do programa!");
	                break;
	            default:
	                printf("\nOpcao Invalida!!!");
	        }
	    } while(menu != 6);
    return 0;
}
