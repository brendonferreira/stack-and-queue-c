#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct Node
{
    char prioridade;
    char id[20];
    struct Node *prox;
} Nodo;

void inicializa_fila(Nodo **N)
{
    *N = NULL;
    //return 0;
}

bool lista_vazia(Nodo **N)
{
    return *N == NULL;
}

Nodo *Cria_Nodo()
{
    Nodo *p;
    p = (Nodo *)malloc(sizeof(Nodo));
    if (!p)
    {
        printf("Problema de alocacao");
        exit(0);
    }
    return p;
}

Nodo *pegar_o_ultimo_no(Nodo *aux)
{
    while (aux->prox != NULL)
        aux = aux->prox;
    return aux;
}

void insere_fim_lista(Nodo **fila, char id[20], char prioridade)
{
    Nodo *aux, *novo;
    
    novo = Cria_Nodo();
    novo->prioridade = prioridade;
    strcpy( novo->id, id );
    novo->prox = NULL;

    if (*fila == NULL)
    {
        *fila = novo;
    }
    else
    {
        aux = *fila;
        while( aux->prox != NULL )
            aux = aux->prox;
        aux->prox = novo;
    }
}

void le_arquivo(Nodo **fila)
{
    FILE *arq;
    Nodo *nodo;

    char string[1280];
    char * prioridade_pointer;
    char * id_pointer;
    char id[20]; 
    char prioridade;
    
    if ((arq = fopen("arquivo.txt", "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
    }

    fgets(string, 1280, arq);


    for (
        id_pointer = strtok(string, ","),
        prioridade_pointer = strtok( NULL, ";" )
        ; 
        id_pointer && prioridade_pointer
        ; 
        id_pointer = strtok(NULL, ","),
        prioridade_pointer = strtok( NULL, ";" ) )
    {
        strcpy( id, id_pointer );
        prioridade = *prioridade_pointer;
        insere_fim_lista( fila, id, prioridade );
    }

    fclose(arq);
}

void imprime_fila(Nodo *fila )
{
    Nodo *aux;
    if (fila == NULL)
    {
        printf("A fila esta vazia!!");
    }
    else
    {
        int i = 0;
        
        for (aux = fila; aux; aux = aux->prox)
        {
            printf("\nid: %s, prio: %c", aux->id, aux->prioridade);
            i++;
        }

    }
}

void imprime_filas(Nodo **queue_entrada, Nodo **queue1, Nodo **queue2, Nodo **queue3)
{
    printf( "\nEspera:\n" );
    imprime_fila( *queue_entrada);
    printf( "\n1:\n" );
    imprime_fila( *queue1 );
    printf( "\n2:\n" );
    imprime_fila( *queue2 );
    printf( "\n3:\n" );
    imprime_fila( *queue3 );
}

int remove_final_lista(Nodo **N)
{
    Nodo *temp, *t;

    if (*N == NULL)
        return 0;
    else
    {

        temp = *N;
        while (temp->prox != NULL)
        {
            t = temp;
            temp = temp->prox;
        }

        // retorno = aux;
        free(t->prox);
        t->prox = NULL;
    }
    return 1;
}

int remove_inicio_lista(Nodo **N)
{
    Nodo *aux, *anterior;
    if (*N == NULL)
        return 0;
    else
    {
        aux = *N;
        while (aux->prox != NULL)
        {
            anterior = aux;
            aux = aux->prox;
        }
        free(aux);
        anterior->prox = NULL;
    }
    return 1;
}

void distribuir_para_filas(Nodo **queue_entrada, Nodo **queue1, Nodo **queue2, Nodo **queue3)
{
    // char um[] = "1";
    // char dois[] = "2";
    // char tres[] = "3";
    // le_arquivo( &queue_entrada );

    char prioridade;
    char id[20];

    while (true)
    {

        Nodo *ultimo_fila = pegar_o_ultimo_no(*queue_entrada);

        prioridade = ultimo_fila->prioridade;
        strcpy( id, ultimo_fila->id );

        printf( "----> prioridade %c -----> id %s\n", prioridade, id );

        imprime_filas( queue_entrada, queue1, queue2, queue3 );
        
        usleep(500 * 1000);
        if ( id != NULL &&  ultimo_fila )
        {
            switch (ultimo_fila->prioridade)
            {
            case '1':
                insere_fim_lista(queue1, id, prioridade);
                // insere_fim_lista(queue1, cpy_ultimo_fila);
                break;
            case '2':
                insere_fim_lista(queue2, id, prioridade);
                // insere_fim_lista(queue2, cpy_ultimo_fila);
                break;
            case '3':
                insere_fim_lista(queue3, id, prioridade);
                // insere_fim_lista(queue3, cpy_ultimo_fila);
                break;
            default:
                break;
            }
        }

        remove_final_lista(queue_entrada);

        // imprime_filas( queue_entrada, queue1, queue2, queue3 );
        
    
    }
}


int main()
{
    Nodo *queue_entrada = NULL, *queue1 = NULL, *queue2 = NULL, *queue3 = NULL;

    inicializa_fila(&queue1);
    inicializa_fila(&queue2);
    inicializa_fila(&queue3);
    inicializa_fila(&queue_entrada);

    le_arquivo(&queue_entrada);

    // imprime_fila( queue_entrada , "FILA DE ENTRADA");

    distribuir_para_filas(&queue_entrada, &queue1, &queue2, &queue3);

    // char string[] = "teste - 123 - oakdasdk";
    // char * s ;
    // s = strtok( string, " - " );
    // printf( "%s\n", s);
    // s = strtok( NULL, " - " );
    // printf( "%s\n", s);
    //    posiciona_em_filas( queue_entrada, queue1, queue2, queue3 );
    //	imprime_fila( queue_entrada, queue1, queue2, queue3 );
    return 0;
}
