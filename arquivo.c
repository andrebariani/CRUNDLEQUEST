#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquivo.h"
#include "lista.h"

// ----------------------------------------------------------
// Funcao ImportarArquivo:  Importa dados de arquivo binario
//             Parametros:  endereco do arquivo, endereco da lista, endereco para
//                          numero de elementos da lista.
//                Retorno:  endereco para primeiro elemento da nova lista;
//                          NULL em caso de arquivo vazio ou nenhum elemento no arquivo.
//
// Observacao: arqsize representa o numero de elemento no arquivo
// ----------------------------------------------------------
_node *ImportarArquivo( FILE *arq, LISTA_LIGADA *l, int *n) {
    ACTOR actor;
    int arqsize;

    if( arq != NULL ) {
        fread( &arqsize , sizeof(int), 1, arq );

        fseek( arq, sizeof(int), SEEK_CUR );

        *n = arqsize;

        while( arqsize ) {
            fread( &(actor), sizeof(ACTOR), 1, arq );
            fseek( arq, sizeof(ACTOR), SEEK_CUR );
            Inserir( l , &actor );
            arqsize--;
        }
        return l->inicio;
    }
    return NULL;
}
// ----------------------------------------------------------
//  Funcao ExportarArquivo: Exporta dados para arquivo binario
//             Parametros:  endereco para arquivo, endereco para lista, numero de
//                          elementos da lista.
// ----------------------------------------------------------
void ExportarArquivo( FILE *arq, LISTA_LIGADA *l, int n ) {

    fwrite( &n , sizeof(int) , 1 , arq );

    fseek( arq, sizeof(n), SEEK_CUR );

    _node *paux = l->inicio;

    if( arq != NULL ) {
        while ( paux != NULL ) {
            fwrite( &(paux->actor) , sizeof(ACTOR) , 1 , arq );

            fseek( arq, sizeof(ACTOR), SEEK_CUR );

            paux = paux->next;
        }
    }
}
// ----------------------------------------------------------
// Funcao ImportarArquivo:  Importa dados de um arquivo .csv
//             Parametros:  endereco para arquivo, endereco para numero
//                          de elementos da lista.
//                Retorno:  endereco para primeiro elemento da nova lista;
//                          NULL em caso de lista vazia.
// ----------------------------------------------------------
_node *ImportarCSV( FILE *arq , int *n ) {
    ACTOR actor;
    LISTA_LIGADA hero;

    hero.inicio = NULL;

    *n = 0;
    int naux = 0;

    while( fscanf( arq, "%[^,],%d,%d,%d,%d,%d,%d\n", actor.nome, &actor.hp, &actor.str, &actor.mag, &actor.def, &actor.res, &actor.spd) != EOF ) {
        Inserir( &hero, &actor );
        naux++;
    }

    *n = naux;
    return hero.inicio;
}
// ----------------------------------------------------------
// Funcao ImportarArquivo:  Exporta dados para um arquivo .csv
//             Parametros:  endereco para arquivo, endereco para lista.
// ----------------------------------------------------------
void ExportarCSV( FILE *arq , LISTA_LIGADA *l ) {

    _node *parq = l->inicio;

    while(parq != NULL) {
        fprintf( arq, "%s,%d,%d,%d,%d,%d,%d\n", parq->actor.nome, parq->actor.hp, parq->actor.str, parq->actor.mag, parq->actor.def, parq->actor.res, parq->actor.spd);
        parq = parq->next;
    }
}
