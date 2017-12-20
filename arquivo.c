#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquivo.h"
#include "lista.h"

// ----------------------------------------------------------
//  Funcao Importar Arquivo: Importa dados do arquivo binario
//                           e retorna uma lista
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
//  Funcao Exportar Arquivo: Exporta dados para arquivo
//                           binario
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
//  Funcao ImportarCSV: Importa dados para um arquivo .csv
// ----------------------------------------------------------
_node *ImportarCSV( FILE *arq , int *n , int sts ) {
    ACTOR actor;
    LISTA_LIGADA hero;

    hero.inicio = NULL;

    *n = 0;
    int naux = 0;

    while( fscanf( arq, "%[^,],%d,%d,%d,%d,%d,%d\n", actor.nome, &actor.hp, &actor.str, &actor.mag, &actor.def, &actor.acc, &actor.spd ) != EOF ) {
        if( sts )
            actor.sts = 1;
        else
            actor.sts = 0;
        Inserir( &hero, &actor );
        naux++;
    }

    *n = naux;
    return hero.inicio;
}
// ----------------------------------------------------------
//  Funcao ExportarCSV: Exporta dados para um arquivo .csv
// ----------------------------------------------------------
void ExportarCSV( FILE *arq , LISTA_LIGADA *l ) {

    _node *parq = l->inicio;

    while(parq != NULL) {
        fprintf( arq, "%s,%d,%d,%d,%d,%d,%d\n", parq->actor.nome, parq->actor.hp, parq->actor.str, parq->actor.mag, parq->actor.def, parq->actor.acc, parq->actor.spd );
        parq = parq->next;
    }
}
