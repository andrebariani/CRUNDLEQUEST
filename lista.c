#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

// insere o elemento no fianl da lista, retorna:
//	0 o elemento for repetido
//	1 se o elemento for inserido com sucesso
// int Inserir( actor **l, int HP, int STR, int MAG, int DEF, int RES, int SPD, char NOME[] ) {
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

// imprime na tela os RAs de todos os alunos com o nome procurado, ou imprime INEXISTENTE
// Retorna o ponteriro do nome procurado se encontrado, ou NULL se inexistente ou não encontrado,
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

//função que remove um elemento da lista com o nome listado, retorna:
//	0 caso o elemento não existe
//	1 caso o elemnto foi removido com sucesso
// int Remover( actor ** l, char NOME[] ) {
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

void LiberarLista( LISTA_LIGADA *primeiro){//limpa a lista, deixando o espaço de memória que ela ocupava vazio
    _node *anterior = primeiro->inicio;
    if(anterior == NULL){	//se a lista estiver vazia, a função nao faz nada
    }else{
        _node *atual = anterior->next;
        if(atual == NULL){	//caso o valor atual seja o unico da lista, ele é liberando
            free(anterior);
        }else{
            while (atual != NULL){		//enquando existir algum elemento da lista, o loop vai liberando um por um os nós da lista
                free(anterior);
                primeiro->inicio = atual;
                anterior = atual;
                atual = anterior->next;
            }
            free(anterior);
        }
    }
    primeiro = NULL;
}
