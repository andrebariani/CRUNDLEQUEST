#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"
// ----------------------------------------------------------
/**
 * @brief Insere elemento na lista ligada.
 *
 * Recebe endereço da lista, endereço do elemento;
 * Retorna 1 em inserção bem-sucedida ou 0 em caso de nome repetido.
 */
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
/**
 * @brief Procura pela lista o nome de um elemento.
 *
 * Recebe endereço da lista, endereço do elemento;
 * Retorna endereço do elemento, ou nulo se não foi encontrado.
 */
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
/**
 * @brief Remove elemento da lista.
 *
 * Recebe endereço da lista, endereço do elemento;
 * Retorna 0 se lista for vazia ou o nome do elemento não foi encontrado,
 * ou retorna 1 se foi encontrado e removido.
 */
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
/**
 * @brief Libera todos os elementos da lista.
 *
 * Recebe endereço da lista.
 */
// ----------------------------------------------------------
void LiberarLista( LISTA_LIGADA *primeiro){//limpa a lista, deixando o espaço de memória que ela ocupava vazio
    primeiro->inicio = NULL;
}
