#ifndef _ARQUIVO_
#define _ARQUIVO_

#include "lista.h"

#define MAX 201

_node *ImportarArquivo( FILE *arq, LISTA_LIGADA *l, int *n );
void ExportarArquivo( FILE *arq, LISTA_LIGADA *l, int n );
_node *ImportarCSV( FILE *arq , int *n , int sts);
void ExportarCSV( FILE *arq , LISTA_LIGADA *l );

#endif
