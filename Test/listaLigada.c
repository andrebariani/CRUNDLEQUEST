#include <stdio.h>
#include <stdlib.h>
#include "archmng.h"

#define REPETIDO "Repetido\n"
#define INEXISTENTE "Nao encontrado\n"


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



void criarLista(LISTA_LIGADA *lista);
int vaziaLista(LISTA_LIGADA *lista);
void apagarLista(LISTA_LIGADA *lista);

// ----------------------------------------------------------
// O Início
// ----------------------------------------------------------

int main() {
  LISTA_LIGADA lista;
  ITEM item;
  NO *search = NULL;
  int i;
  FILE *fr, *fw;

  //criar a lista
  criarLista(&lista);

  fr = fopen ("lista.txt", "rw");

      //le linha a linha do arquivo e insere na lista
      while (fscanf(fr, "%d %d", &item.chave, &item.valor) != EOF)
        inserirLista(&lista, &item);

    int opt = 1;
    while( opt != 0 ) {
        scanf("%d", &opt);
        switch( opt ) {

            case 1:
                scanf("%d %d", &item.chave, &item.valor);
                inserirLista(&lista, &item) ? : printf(REPETIDO);
            break;

            case 2:
                scanf("%d", &item.chave);
                search = buscar(&lista, &item);
                if(search == NULL) {
                    printf(INEXISTENTE);
                    break;
                }
                scanf("%d %d", &item.chave, &item.valor);
                search->item.chave = item.chave;
                search->item.valor = item.valor;
            break;

            case 3:
                scanf("%d", &item.chave);
                remover(&lista, &item);
            break;

            case 4:
                scanf("%d", &item.chave);
                search = buscar(&lista, &item);
                if(search == NULL) {
                    printf(INEXISTENTE);
                    break;
                }
                printf("%d %d\n", search->item.chave, search->item.valor);
            break;

            case 5:
                printf("--- Lista --- \n");
                imprimirLista(&lista);
            break;
        }
    }
          //Salva lista em outro arquivo
    fw = fopen ("lista.txt", "w");
    if (!vaziaLista(&lista)){
        NO *paux = lista.inicio;

        while (paux != NULL) {
            fprintf(fw, "%d %d\n", paux->item.chave, paux->item.valor);
            paux = paux->next;
        }
    }

  apagarLista(&lista);
  fclose(fr);
  fclose(fw);

  return 0;
}

// ----------------------------------------------------------
// Criar Lista
// ----------------------------------------------------------

// inicializa campos inicio e fim da LISTA com NULL
void criarLista(LISTA_LIGADA *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
}

// ----------------------------------------------------------
// Lista Vazia
// ----------------------------------------------------------

// verifica se inicio da lista � NULL
int vaziaLista(LISTA_LIGADA *lista) {
  return (lista->inicio == NULL);
}

// ----------------------------------------------------------
// Apagar Lista
// ----------------------------------------------------------

void apagarLista(LISTA_LIGADA *lista) {
  if (!vaziaLista(lista)) {
    NO *paux = lista->inicio;

    while (paux != NULL) {
      NO *prem = paux;
      paux = paux->next;
      free(prem);
    }
  }

  lista->inicio = NULL;
  lista->fim = NULL;
}
