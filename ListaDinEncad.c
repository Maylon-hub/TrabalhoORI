#include "ListaDinEncad.h" //inclui os Prot�tipos
#include "Set.h"
#include <stdio.h>
#include <stdlib.h>

Lista *cria_lista() {
  Lista *li = (Lista *)malloc(sizeof(Lista));
  if (li != NULL)
    li->inicio = NULL; // Inicializa a lista vazia
    li->qnt = 0;
  return li;
}

Nodo *criaNodo(int valor) {
  Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
  if (novo != NULL) {
    novo->valor = valor;
    novo->prox = NULL;
  }
  return novo;
}

int insere_lista_inicio(Lista *li, int val) {
  if (li == NULL)
    return 0;
  Nodo *novo = criaNodo(val);
  if (novo == NULL)
    return 0;
  novo->prox = li->inicio;
  li->inicio = novo;
    li->qnt++;
  return 1;
}

int tamanhoLista(Lista* li) {
    if (li == NULL) return 0;  // Verifica se a lista é válida

    return li->qnt;
}

Set* percorreLista(Lista* li) {
    if (li == NULL) return 0;  // Verifica se a lista é válida
    Set* dados;   
    Nodo* temp = li->inicio;

    while (temp != NULL) {
        insereSet(dados, temp->valor);
        temp = temp->prox;
    }
  
    return dados; 
}

// Função para imprimir a lista encadeada
void imprimeLista(Lista* li) {
    if (li == NULL) return;  // Verifica se a lista é válida

    Nodo* temp = li->inicio;
    while (temp != NULL) {
        printf("%d -> ", temp->valor);
        temp = temp->prox;
    }
    printf("NULL\n");
}