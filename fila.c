#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

typedef struct Node {
	char *prioridade;
	char *id;
	struct Node *prox;
} Nodo;

int inicializa_fila(Nodo **N) {
    *N = NULL;
    return 0;
}

bool lista_vazia( Nodo ** N ) {
    return *N == NULL;
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

void insere_fim_lista(Nodo **fila, Nodo *novo) {
	Nodo *aux;
	if(*fila == NULL){
	    *fila = novo;
	} else {
	    aux = pegar_o_ultimo_no( *fila );
	    aux->prox = novo;
    }
    // imprime_fila( fila , "lasdk");
    // printf( "\nlaskdlaksldkasdkl -> %s", pegar_o_ultimo_no( *fila )->id );
}

void le_arquivo(Nodo **fila){
    FILE *arq;
    Nodo * nodo;
    
	char string[1280];
    
    if((arq = fopen("arquivo.txt", "r")) == NULL){
    	printf("Erro ao abrir o arquivo.\n");
	}
    
    fgets(string, 1280, arq);
    
    
    nodo = Cria_Nodo();
    nodo->id = strtok(string,",");
    nodo->prioridade = strtok(NULL,";");

    while( nodo->id != NULL && nodo->prioridade != NULL ){
        insere_fim_lista( fila, nodo );
        nodo = Cria_Nodo();
        nodo->id = strtok(NULL,",");
        nodo->prioridade = strtok(NULL,";");
    }
    fclose(arq);
}


void imprime_fila( Nodo * file, char nome[] ) {
    Nodo *aux;
    if(file == NULL) {}
        // printf("A fila esta vazia!!");
    else {
        int i = 0;
        printf("Fila de %s");
        for(aux = file; aux != NULL; aux = aux->prox) { 
            printf("\n%d - id: %s, prio: %s\n", i, nome, aux->id, aux->prioridade);
            i++;
        }
    }
}

void imprime_filas(Nodo *queue_espera, Nodo *queue1, Nodo *queue2, Nodo *queue3 ) {
    imprime_fila( queue_espera, "Espera");
    imprime_fila( queue1, "1");
    imprime_fila( queue2, "2");
    imprime_fila( queue3, "3");
}

// int remove_final_lista(Nodo **N) {
//     Nodo *aux, *anterior;
//     if(*N == NULL)
//         return 0;
//     else {

//         aux = *N;
//         while(aux->prox != NULL) {
//             anterior = aux;
//             aux = aux->prox;
//         }
        
//         // retorno = aux;
//         free( aux );
//         anterior->prox = NULL;
//     }
//     return 1;
// }

int remove_final_lista(Nodo **N) {
    Nodo *temp, *t;

    if(*N == NULL)
        return 0;
    else {

        temp = *N;
        while(temp->prox != NULL) {
            t = temp;
            temp = temp->prox;
        }
        
        // retorno = aux;
        free( t->prox );
        t->prox = NULL;
    }
    return 1;
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


void distribuir_para_filas( Nodo **queue_entrada, Nodo **queue1, Nodo **queue2, Nodo **queue3 ){
	// char um[] = "1";
	// char dois[] = "2";
	// char tres[] = "3";
    // le_arquivo( &queue_entrada );
    
    Nodo * cpy_ultimo_fila = Cria_Nodo();
    Nodo * ultimo_fila = pegar_o_ultimo_no( *queue_entrada );
    cpy_ultimo_fila->id = ultimo_fila->id;
    cpy_ultimo_fila->prioridade = ultimo_fila->prioridade;
    remove_final_lista( queue_entrada );

    if ( cpy_ultimo_fila != NULL && cpy_ultimo_fila->id && cpy_ultimo_fila->prioridade ) {
        switch( *( cpy_ultimo_fila->prioridade ) ) {
            case '1': 
                insere_fim_lista( queue1, cpy_ultimo_fila ); break;
            case '2': 
                insere_fim_lista( queue2, cpy_ultimo_fila ); break;
            case '3': 
                insere_fim_lista( queue3, cpy_ultimo_fila ); break;
            default: 
                insere_fim_lista( queue_entrada, cpy_ultimo_fila ); break;
             
        }
    } else {
        printf("CABO SSSA PORRA");
    }

    imprime_fila( *queue_entrada , "sdasd");
    // imprime_filas( *queue_entrada, *queue1, *queue2, *queue3 );

    
    // delay( 500 );

    usleep( 500 * 1000 );


    distribuir_para_filas( queue_entrada, queue1, queue2, queue3 );
}



int main(){
    Nodo *queue_espera = NULL, *queue1 = NULL, *queue2 = NULL, *queue3 = NULL; 
    
    inicializa_fila( &queue1 );
    inicializa_fila( &queue2 );
    inicializa_fila( &queue3 );
    inicializa_fila( &queue_espera );
    
    le_arquivo(&queue_espera);

    distribuir_para_filas( &queue_espera, &queue1, &queue2, &queue3 );

    
    
    // char string[] = "teste - 123 - oakdasdk";
    // char * s ;
    // s = strtok( string, " - " );
    // printf( "%s\n", s);
    // s = strtok( NULL, " - " );
    // printf( "%s\n", s);
//    posiciona_em_filas( queue_espera, queue1, queue2, queue3 );
//	imprime_fila( queue_espera, queue1, queue2, queue3 ); 
    return 0;
}
