#include "Set.h"
// Estrutura para um nó da lista encadeada
struct nodo {
    int valor;
    struct nodo *prox;
};

typedef struct nodo Nodo;

// Estrutura da lista encadeada
struct lista {
    Nodo *inicio;
    int qnt; 
};

typedef struct lista Lista;

Lista* cria_lista();
Nodo* criaNodo(int valor);
void imprimeLista(Lista* li);
int tamanhoLista(Lista* li);
//void libera_lista(Lista* li);
int insere_lista_inicio(Lista* li, int numero_tweet);
//int remove_lista(Lista* li, int mat);
//int remove_lista_inicio(Lista* li);
//int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
//int lista_vazia(Lista* li);
void imprime_lista(Lista* li);
//int consulta_lista_mat(Lista* li, int mat, struct aluno *al);
Set* percorre_lista(Lista li);