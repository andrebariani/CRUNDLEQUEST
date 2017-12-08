#include <stdio.h>
#include <stdlib.h>


typedef struct {
  int chave;
  int valor;
} ITEM;

typedef struct NO {
  ITEM item;
  struct NO *proximo;
} NO;

typedef struct {
  NO *inicio;
  NO *fim;
} LISTA_LIGADA;



void criarLista(LISTA_LIGADA *lista);
int vaziaLista(LISTA_LIGADA *lista);
int inserirLista(LISTA_LIGADA *lista, ITEM *item);
void imprimirLista(LISTA_LIGADA *lista);
void apagarLista(LISTA_LIGADA *lista);



int main() {
  LISTA_LIGADA lista;
  ITEM item;
  int i;
  FILE *fr, *fw;

  //criar a lista
  criarLista(&lista);

  fr = fopen ("lista-in.txt", "r");

  //le linha a linha do arquivo e insere na lista
  while (fscanf(fr, "%d %d", &item.chave, &item.valor) != EOF)
    inserirLista(&lista, &item);

  printf("--- Lista --- \n");
  imprimirLista(&lista);


  //Salva lista em outro arquivo
  fw = fopen ("lista-out.txt", "w");
  if (!vaziaLista(&lista)){
    NO *paux = lista.inicio;

    while (paux != NULL) {
      fprintf(fw, "%d %d\n", paux->item.chave, paux->item.valor);
      paux = paux->proximo;
    }
  }


  apagarLista(&lista);
  fclose(fr);
  fclose(fw);

  return 0;
}



// inicializa campos inicio e fim da LISTA com NULL
void criarLista(LISTA_LIGADA *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
}

// verifica se inicio da lista � NULL
int vaziaLista(LISTA_LIGADA *lista) {
  return (lista->inicio == NULL);
}

void imprimirLista(LISTA_LIGADA *lista) {

  if (!vaziaLista(lista)){
    NO *paux = lista->inicio;

    while (paux != NULL) {
      printf("%d - %d\n", paux->item.chave, paux->item.valor);
      paux = paux->proximo;
    }
  }
  else
    printf("LISTA VAZIA!\n\n");

}


// Insere na ultima posicao
int inserirLista(LISTA_LIGADA *lista, ITEM *item) {
  //cria um novo n�
  NO *pnovo = (NO *)malloc(sizeof(NO));

  if (pnovo != NULL) { //verifica se a mem�ria foi alocada
    pnovo->item = *item; //preenche os dados
    pnovo->proximo = NULL; //define que o pr�ximo � nulo

    if (vaziaLista(lista)) { //se a lista for vazia
      lista->inicio = pnovo; //inicio aponta para novo
    } else {
      lista->fim->proximo = pnovo; //proximo do fim aponto para novo
    }

    lista->fim = pnovo; //fim aponta para novo

    return 1;
  } else {
    return 0;
  }
}

void apagarLista(LISTA_LIGADA *lista) {
  if (!vaziaLista(lista)) {
    NO *paux = lista->inicio;

    while (paux != NULL) {
      NO *prem = paux;
      paux = paux->proximo;
      free(prem);
    }
  }

  lista->inicio = NULL;
  lista->fim = NULL;
}
