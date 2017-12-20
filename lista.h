#ifndef _LISTA_
#define _LISTA_

#define MAX 201

typedef struct {
    int hp, str, mag, def, acc, spd, sts;
    int turndefend;
    char nome[MAX];
} ACTOR;

typedef struct _node{
    struct _node *next;
    ACTOR actor;
}_node;

typedef struct {
    _node *inicio;
} LISTA_LIGADA;

int Inserir( LISTA_LIGADA *l, ACTOR *actor );
_node *Procurar( LISTA_LIGADA *l, ACTOR *actor );
int Remover( LISTA_LIGADA *l, ACTOR *actor );
void LiberarLista( LISTA_LIGADA *primeiro );

#endif
