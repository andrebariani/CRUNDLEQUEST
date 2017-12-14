#ifndef _LISTA_
#define _LISTA_

#define MAX 201

typedef struct {
    int hp, str, mag, def, res, spd, sts;
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
_node *Procurar_pelo_nome( LISTA_LIGADA *l, ACTOR *actor );
int Remover( LISTA_LIGADA *l, ACTOR *actor );
void libera_lista( LISTA_LIGADA *primeiro );

#endif
