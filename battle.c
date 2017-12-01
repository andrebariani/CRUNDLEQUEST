/* ================================================================== *
  Universidade Federal de Sao Carlos - UFSCar, Sorocaba

  Disciplina: Algoritmos e Programação 2

  Lista 05 - Exercício 01 - Lista de RA

* ================================================================== *
  Dados do aluno:

  RA: 743506
  Nome: Andre Matheus Bariani Trava

* ================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// menu de opcoes
#define SAIR            0
#define INSERIRHERO     1
#define INSERIRENEMY    2
#define REMOVER         3
#define IMPRIMIR        4

// classes

#define MAGE    11
#define FIGHTER 22

// constantes
#define MAX     200

// frases pre-definidas
#define REPETIDO "REPETIDO\n"
#define INEXISTENTE "INEXISTENTE\n"

//REGISTROS
typedef struct _node{
    struct _node *next;
    struct _node *prev;
    int hp, str, mag, def, res, spd, sts, class;
    int turndefend;
    char nome[MAX];
}actor;

// PROTOTIPO DAS FUNCOES
//
// int battlestart( actor ** h, actor ** e, int hn, int en );
// actor ** turnmaker( actor *headh, actor *heade );
int Inserir( actor ** l, int HP, int STR, int MAG, int DEF, int RES, int SPD, int CLASS, int STS, char NOME[] );
void InserirCampos( actor *p, int HP, int STR, int MAG, int DEF, int RES, int SPD, int CLASS, int STS, char NOME[] );
int ProcurarRAnome( actor ** l, char NOME[] );         // imprime na tela os RAs de todos os alunos com o nome procurado, ou retorna 0 e imprime INEXISTENTE
void Remover( actor ** l, char NOME[] );                  // remove da actora o aluno
void Imprimir( actor** l );                        // exibe uma linha na tela com todos os RAs da lista

// ROTINA PRINCIPAL

int main() {
    actor *h = NULL;
    actor *e = NULL;

    int HP, STR, MAG, DEF, RES, SPD, CLASS, type, hn = 0, en = 0;
    char NAME[MAX];

    int opt = 1;
    while(opt != 0) {
       scanf("%d",&opt);
       switch(opt){

          case INSERIRHERO:
            scanf("%d", &HP);
            scanf("%d", &STR);
            scanf("%d", &MAG);
            scanf("%d", &DEF);
            scanf("%d", &RES);
            scanf("%d", &SPD);
            scanf("%d", &type );
            scanf("\n%400[^\n]", NAME);
            if( Inserir( &h, HP, STR, MAG, DEF, RES, SPD, CLASS, type, NAME ) ) {
                hn++;
            }
            else{
                printf(REPETIDO);
            }
          break;

          case INSERIRENEMY:
            scanf("%d", &HP);
            scanf("%d", &STR);
            scanf("%d", &MAG);
            scanf("%d", &DEF);
            scanf("%d", &RES);
            scanf("%d", &SPD);
            scanf("%d", &type );
            scanf("\n%400[^\n]", NAME);
            if( Inserir( &e, HP, STR, MAG, DEF, RES, SPD, CLASS, type, NAME ) ) {
                en++;
            }
            else{
                printf(REPETIDO);
            }
            break;

          case REMOVER:
            scanf("\n%400[^\n]", NAME);
            scanf("%d\n", &type);
            type ? Remover( &h, NAME ) : Remover( &e, NAME );
          break;

          case IMPRIMIR:
            scanf("%d\n", type);
            type ? Imprimir( &h ) : Imprimir( &e );
          break;

       }
    }

    printf("Party inserida!\n");

    // battlestart( &h, &e, hn, en ) ? printf("You Win!\n") : printf("You Lose!\n"); ;

    return 0;
}
//
// actor ** turnmaker( actor * headh, actor * heade ) {
//     actor *headt = NULL;
//     actor *h = headh;
//     actor *e = heade;
//     int aux;
//
//     if( headh == NULL && heade == NULL )
//         return **headt;
//
//     while( h != NULL ) {
//         aux = Inserir( &headt, h->hp, h->str, h->mag, h->def, h->res, h->spd, h->class, h->sts, h->nome );
//         h = h->next;
//     }
//
//     while( e != NULL ) {
//         aux = Inserir( &headt, e->hp, e->str, e->mag, e->def, e->res, e->spd, e->class, e->sts, e->nome );
//         e = e->next;
//     }
//
//     return **headt;
// }
//
// int battlestart( actor ** h, actor ** e, int hn, int en) {
//     actor *headt = NULL;
//     int opt;
//
//     srand(time(NULL));
//
//     headt = turnmaker( h, e );
//
//     actor *t = headt;
//
//     while( 1 ) {
//         if( t == NULL ){
//             *t = &headt;
//         }
//         switch(t->sts) {
//             // hero
//             case 1:
//                 t->turndefend = 0;
//                 scanf("%d\n", opt);
//                 switch(opt) {
//                     case 1:
//                         actor *at = headt;
//                         int aux = en;
//                         int r = 0;
//
//                         while ( r != 0 )
//                             r = rand() % en;
//
//                         while( at != NULL ) {
//                             if( at->sts == 0 ){
//                                 if( aux == r ) {
//                                     if(t->class == MAGE) {
//                                         at->hp -= t->mag - t->res;
//                                         if( at->hp < 0 ) {
//                                             en--;
//                                             Remover( &at, at->nome );
//                                         }
//                                         break;
//                                     }
//                                     else if(t->class == FIGHTER) {
//                                         at->hp -= (t->str - (at->def + at->turndefend));
//                                         if( at->hp < 0 ) {
//                                             en--;
//                                             Remover( &at, at->nome );
//                                         }
//                                         break;
//                                     }
//                                 }
//                                 else
//                                     aux--;
//                             }
//                             at = at->next;
//                         }
//                     break;
//
//                     case 0:
//                         t->turndefend = t->def * 1.2;
//                     break;
//                 }
//             break;
//
//             // enemy
//             case 0:
//                 t->turndefend = 0;
//                 r = rand() % 1;
//                 switch(opt) {
//                     case 1:
//                         actor *at = headt;
//                         int aux = en;
//                         int r = 0;
//
//                         while ( r != 0 )
//                             r = rand() % en;
//
//                         while( at != NULL ) {
//                             if( at->sts == 1 ){
//                                 if( aux == r ) {
//                                     if(t->class == MAGE) {
//                                         at->hp -= t->mag - t->res;
//                                         if( at->hp < 0 ) {
//                                             hn--;
//                                             Remover( &at, at->nome );
//                                         }
//                                         break;
//                                     }
//                                     else if(t->class == FIGHTER) {
//                                         at->hp -= (t->str - (at->def + at->turndefend));
//                                         if( at->hp < 0 ) {
//                                             hn--;
//                                             Remover( &at, at->nome );
//                                         }
//                                         break;
//                                     }
//                                 }
//                                 else
//                                     aux--;
//                             }
//                             at = at->next;
//                         }
//                     break;
//
//                     case 0:
//                         t->turndefend = t->def * 1.2;
//                         break;
//             }
//             break;
//         }
//
//         if(en == 0) {
//             return 1;
//         }
//
//         if(hn == 0) {
//             return 0;
//         }
//
//         t = t->next;
//     }
// }

// insere o aluno na posicao correta da actora, ou 0 se repetido
void InserirCampos( actor * p, int HP, int STR, int MAG, int DEF, int RES, int SPD, int CLASS, int STS, char NOME[] ) {
    p->hp = HP;
    p->str = STR;
    p->mag = MAG;
    p->def = DEF;
    p->res = RES;
    p->spd = SPD;
    p->class = CLASS;
    p->sts = STS;

    strcpy(p->nome, NOME);
}

int Inserir( actor ** l, int HP, int STR, int MAG, int DEF, int RES, int SPD, int CLASS, int STS, char NOME[] ) {

    if( *l == NULL ) {
        actor *p = (actor*)malloc(sizeof(actor));

        InserirCampos( p, HP, STR, MAG, DEF, RES, SPD, CLASS, STS, NOME );

        *l = p;
        p->next = NULL;
        p->prev = NULL;

        return 1;
    }
    else {
        actor *p = *l;
        int first = 1;

        while ( 1 ) {
            if ( strcmp(NOME, p->nome) == 0  )
                return 0;

            if( p->spd < SPD ) {
                actor *new = (actor*)malloc(sizeof(actor));
                if ( first ) {

                    InserirCampos( new, HP, STR, MAG, DEF, RES, SPD, CLASS, STS, NOME );
                    *l = new;
                    new->next = p;
                    p->prev = new;
                    new->prev = NULL;
                    return 1;
                }
                InserirCampos( new, HP, STR, MAG, DEF, RES, SPD, CLASS, STS, NOME );
                new->prev = p->prev;
                p->prev->next = new;
                p->prev = new;
                new->next = p;
                return 1;
            }
            else if( p->next == NULL ){
                actor *new = (actor*)malloc(sizeof(actor));

                InserirCampos( new, HP, STR, MAG, DEF, RES, SPD, CLASS, STS, NOME );

                p->next = new;
                new->prev = p;
                new->next = NULL;
                return 1;
            }
            p = p->next;
            first = 0;
        }

    }

}

// imprime na tela os RAs de todos os alunos com o nome procurado, ou imprime INEXISTENTE
// Retorna 1 se encontrado, ou 0 se inexistente
int ProcurarRAnome( actor ** l, char NOME[] ) {

    if( *l == NULL )
        return 0;

    actor *p = *l;
    int found = 0;

    while( p != NULL ) {
        if( strcmp(NOME, p->nome) == 0 ) {
            found++;
        }
        p = p->next;
    }

    if(found == 0) {
        return 0;
    }

    printf("\n");

    return 1;
}

void Remover( actor ** l, char NOME[] ) {

    if(*l == NULL)
        return;

    actor *p = *l;
    int first = 1;

    while ( p != NULL ) {
        if( strcmp(NOME, p->nome) == 0 ) {
            if( first ) {
                if( p->next == NULL && p->prev == NULL ) {         // Se for o unico item da actora
                    free(p);
                    *l = NULL;
                    return;
                }
                *l = p->next;                                     // Se for o primeiro item da actora
                free(p);
                return;
            }
            if( p->next == NULL ) {                               // Se for o ultimo item da actora
                p->prev->next = NULL;
                free(p);
                return;
            }
            p->prev->next = p->next;
            free(p);
            return;
        }
        p = p->next;
        first = 0;
    }

}

void Imprimir( actor** l ) {

    if( *l == NULL )
        return;

    actor * p = *l;

    while( p != NULL ) {
        printf("||Name: %s\t\t||\n", p->nome);
        printf("||HP:  %d\t\t||\n", p->hp);
        printf("||STR: %d\t\t||\n", p->str);
        printf("||MAG: %d\t\t||\n", p->mag);
        printf("||DEF: %d\t\t||\n", p->def);
        printf("||RES: %d\t\t||\n", p->res);
        printf("||SPD: %d\t\t||\n\n", p->spd);

        p = p->next;
    }

    printf("\n");
}
