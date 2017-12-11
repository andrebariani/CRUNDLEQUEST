#include <stdio.h>
#include <stdlib.h>

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
void alterarLista(LISTA_LIGADA *lista, ITEM *item);
NO *buscar(LISTA_LIGADA *lista, ITEM *item);
int remover(LISTA_LIGADA *lista, ITEM *item);
int inserirLista(LISTA_LIGADA *lista, ITEM *item);
void imprimirLista(LISTA_LIGADA *lista);
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
// Imprimir Listas
// ----------------------------------------------------------

void imprimirLista(LISTA_LIGADA *lista) {

  if (!vaziaLista(lista)){
    NO *paux = lista->inicio;

    while (paux != NULL) {
      printf("%d - %d\n", paux->item.chave, paux->item.valor);
      paux = paux->next;
    }
  }
  else
    printf("LISTA VAZIA!\n\n");

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
