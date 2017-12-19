#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

// ----------------------------------------------------------
// Funcao Inserir:  Insere elemento na lista.
//     Parametros:  endereco para lista, endereco para elemento.
//        Retorno:  1 em caso de insercao feita;
//                  0 em caso de elemento repetido.
// ----------------------------------------------------------
int Inserir( LISTA_LIGADA *l, ACTOR *actor ) {

    if( l->inicio == NULL ) {
        _node *new = (_node*)malloc(sizeof(_node));

        new->actor = *actor;

        l->inicio = new;
        new->next = NULL;

        return 1;
    }
    else {
        _node *paux = l->inicio;

        while ( 1 ) {
            if ( strcmp(actor->nome, paux->actor.nome) == 0  )
                return 0;

            else if( paux->next == NULL ){
                _node *new = (_node*)malloc(sizeof(_node));

                new->actor = *actor;

                paux->next = new;
                new->next = NULL;
                return 1;
            }
            paux = paux->next;
        }
    }
}

// ----------------------------------------------------------
// Funcao Procurar: Procura elemento pelo nome.
//      Parametros: endereco para lista, endereco para elemento.
//         Retorno: endereco para o elemento encontrado;
//                  NULL em caso de elemento nao encontrado.
// ----------------------------------------------------------
_node *Procurar( LISTA_LIGADA *l, ACTOR *actor ) {

    if( l->inicio == NULL )
        return NULL;

    _node *paux = l->inicio;

    while( paux != NULL ) {
        if( strcmp( paux->actor.nome, actor->nome) == 0 ) {
            return paux;
        }
        paux = paux->next;
    }

    return NULL;
}

// ----------------------------------------------------------
// Funcao Remover:  Remove elemento com o nome indicado da lista.
//     Parametros:  endereco para lista, endereco para elemento.
//        Retorno:  1 em caso de remocao feita;
//                  0 em caso de elemento nao encontrado ou lista vazia.
// ----------------------------------------------------------
int Remover( LISTA_LIGADA *l, ACTOR *actor ) {

    if(l->inicio == NULL)
        return 0;

    _node *p = l->inicio;
    _node *panterior = l->inicio;
    int first = 1;

        while ( p != NULL ) {
            if( strcmp( p->actor.nome, actor->nome) == 0 ) {
                if( first ) {                                         // Se for o primeiro item da lista
                    if( p->next == NULL ) {                           // Se for o unico item da lista
                        free(p);
                        l->inicio = NULL;
                        return 1;
                    }
                    l->inicio = p->next;
                    free(p);
                    return 1;
                }
                if( p->next == NULL ) {                               // Se for o ultimo item da lista
                    free(p);
                    panterior->next = NULL;
                    return 1;
                }
                panterior->next = p->next;
                free(p);
                return 1;
            }
            panterior = p;
            p = p->next;
            first = 0;
        }
    return 0;
}

// ----------------------------------------------------------
// Funcao LiberarLista: limpa a lista, deixando o espaço de memoria que ela ocupava vazio
//          Parametros: endereco para lista
// ----------------------------------------------------------
void LiberarLista( LISTA_LIGADA *primeiro){//limpa a lista, deixando o espaço de memória que ela ocupava vazio
    primeiro->inicio = NULL;
}
