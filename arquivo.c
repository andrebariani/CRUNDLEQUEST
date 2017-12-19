#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquivo.h"
#include "lista.h"

// ----------------------------------------------------------
//  Funcao Importar Arquivo: Importa dados binarios do Arquivo
//                           e retorna em uma lista
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
// printf("JooJ\n");
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
