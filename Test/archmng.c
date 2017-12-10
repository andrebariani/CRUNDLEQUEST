#include <stdio.h>
#include <stdlib.h>
#include "archmng.h"

typedef struct {
  int chave;
  int valor;
} ITEM;

typedef struct NO {
  ITEM item;
  struct NO *next;
  struct NO *prev;
} NO;

typedef struct {
  NO *inicio;
  NO *fim;
} LISTA_LIGADA;

NO *buscar(LISTA_LIGADA *lista, ITEM *item);
int remover(LISTA_LIGADA *lista, ITEM *item);
int inserirLista(LISTA_LIGADA *lista, ITEM *item);
void imprimirLista(LISTA_LIGADA *lista);
int vaziaLista(LISTA_LIGADA *lista);


// ----------------------------------------------------------
// Imprimir Listas
// ----------------------------------------------------------

void imprimirLista(LISTA_LIGADA *lista) {
    NO *paux = lista->inicio;

    if(paux == NULL) {
        printf("LISTA VAZIA!\n\n");
        return;
    }
    while (paux != NULL) {
      printf("%d - %d\n", paux->item.chave, paux->item.valor);
      paux = paux->next;
    }
}

// ----------------------------------------------------------
// Inserir
// ----------------------------------------------------------

// Insere na ultima posicao
int inserirLista(LISTA_LIGADA *lista, ITEM *item) {
  //cria um novo n�
  NO *pnovo = (NO *)malloc(sizeof(NO));
  NO *paux = buscar(lista, item);

  if(paux != NULL)
    return 0;

  if (pnovo != NULL) { //verifica se a mem�ria foi alocada
    pnovo->item = *item; //preenche os dados
    pnovo->next = NULL; //define que o pr�ximo � nulo
    pnovo->prev = NULL;

    if (vaziaLista(lista)) { //se a lista for vazia
      lista->inicio = pnovo; //inicio aponta para novo
    } else {
      lista->fim->next = pnovo; //next do fim aponto para novo
      pnovo->prev = lista->fim;
    }

    lista->fim = pnovo; //fim aponta para novo

    return 1;
  } else {
    return 0;
  }
}

// ----------------------------------------------------------
// Buscar por chave
// ----------------------------------------------------------


NO *buscar(LISTA_LIGADA *lista, ITEM *item) {
    if(lista == NULL)
        return NULL;

    NO *search = lista->inicio;

    // printf("First items are: %d\n", search->item.chave );
    while( search != NULL ) {
// printf("Into Buscar...\n" );
        if( search->item.chave == item->chave ) {
            printf("Into Buscar...\n" );
            return search;
        }
        search = search->next;
    }
    return NULL;
}

// ----------------------------------------------------------
// Remover
// ----------------------------------------------------------

int remover(LISTA_LIGADA *lista, ITEM *item) {

    NO *rem = buscar(lista, item);

    if(rem == NULL)
        return 0;

    if(rem->next == NULL && rem->prev == NULL ) {
        free(rem);
        lista->inicio = NULL;
        lista->fim = NULL;
    }
    else if( rem == lista->inicio ) {
        lista->inicio = rem->next;
        free(rem);
    }
    else if( rem == lista->fim ) {
        lista->fim = rem->prev;
        rem->prev->next = NULL;
        free(rem);
    } else {
        rem->prev->next = rem->next;
        free(rem);
    }

    return 1;
}

// ----------------------------------------------------------
// Lista Vazia
// ----------------------------------------------------------


int vaziaLista(LISTA_LIGADA *lista) {
  return (lista->inicio == NULL);
}
