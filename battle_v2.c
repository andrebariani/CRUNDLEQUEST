#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ----------------------------------------------------------
// Bibliotecas internas
// ----------------------------------------------------------
#include "lista.h"

// ----------------------------------------------------------
// Opcoes do Menu
// ----------------------------------------------------------
#define SAIR 			0
#define INSERIR_HERO	1
#define INSERIR_ENEMY	2
#define PROCURAR		3
#define REMOVER			4
#define IMPRIMIR		5


// ----------------------------------------------------------
// Constantes
// ----------------------------------------------------------

#define MAX     201

// ----------------------------------------------------------
// Frases Pre-definidas
// ----------------------------------------------------------

#define REPETIDO "REPETIDO\n"
#define INEXISTENTE "INEXISTENTE\n"

// ----------------------------------------------------------
// REGISTROS
// ----------------------------------------------------------

// typedef struct {
//     int hp, str, mag, def, res, spd, sts;
//     int turndefend;
//     char nome[MAX];
// } ACTOR;
//
// typedef struct _node{
//     struct _node *next;
//     ACTOR actor;
// }_node;
//
// typedef struct {
//     _node *inicio;
// } LISTA_LIGADA;

// ----------------------------------------------------------
// Prototipo das funcoes
// ----------------------------------------------------------
// int battlestart( actor ** h, actor ** e, int hn, int en );
// actor ** turnmaker( actor *headh, actor *heade );
void Imprimir( LISTA_LIGADA *l );
void ImprimirElemento( _node *escolhido );

// ----------------------------------------------------------
// Rotina Principal
// ----------------------------------------------------------
int main() {
    LISTA_LIGADA hero;
    LISTA_LIGADA enemy;
    ACTOR actor;
	_node *escolhido = NULL;
    int hero_number = 0, enemy_number = 0, type;

    // Inicializa as listas
    hero.inicio = NULL;
    enemy.inicio = NULL;
    // ------------------------------------------------------

    // Arquivos
    FILE *heroarq;
    FILE *enemyarq;
    printf("JooJ\n" );
    heroarq = fopen("herobd.dat", "rb");
    enemyarq = fopen("enemybd.dat", "rb");

    int arqsize;

    if( heroarq != NULL ) {
        printf("JooJ\n" );
        fread( &arqsize , sizeof(int), 1, heroarq );
        printf("JooJ\n" );

        fseek( heroarq, sizeof(arqsize), SEEK_CUR );

        hero_number = arqsize;

        while( arqsize ) {
            fread( &actor, sizeof(ACTOR), 1, heroarq );

            fseek( heroarq, sizeof(ACTOR), SEEK_CUR );

            Inserir( &hero , &actor );
            arqsize--;
        }
    }
    if( enemyarq != NULL ) {

        fread( &arqsize, sizeof(int), 1, enemyarq );

        fseek( enemyarq, sizeof(arqsize), SEEK_CUR );

        enemy_number = arqsize;

        while( arqsize ) {
            fread( &actor, sizeof(ACTOR), 1, enemyarq );

            fseek( enemyarq, sizeof(ACTOR), SEEK_CUR );

            Inserir( &enemy , &actor );
            arqsize--;
        }
    }
    // ------------------------------------------------------


    printf("hero number: %d\n", hero_number );
    printf("enemy number: %d\n", enemy_number );


    int opt = 1;
    while(opt != 0) {
	   scanf("%d",&opt);
       switch(opt){

          case INSERIR_HERO:
            actor.turndefend = 0;
            printf("Insira os seguintes dados:\n");
			printf("HP:");
            scanf("%d", &actor.hp);
            printf("Força:");
            scanf("%d", &actor.str);
            printf("Magia:");
            scanf("%d", &actor.mag);
            printf("Defesa:");
            scanf("%d", &actor.def);
            printf("Resistencia:");
            scanf("%d", &actor.res);
            printf("Velociadade:");
            scanf("%d", &actor.spd);
            getchar();
            printf("Nome do Héroi:");
            scanf("%[^\n]", actor.nome);
            if( Inserir( &hero, &actor ) ) {
                printf("Héroi inserido com susesso!\n");
                hero_number++;
            }
            else{
                printf(REPETIDO);
            }
          break;

          case INSERIR_ENEMY:
            actor.turndefend = 0;
            printf("Insira os seguintes dados:\n");
            printf("HP:");
            scanf("%d", &actor.hp);
            printf("Força:");
            scanf("%d", &actor.str);
            printf("Magia:");
            scanf("%d", &actor.mag);
            printf("Defesa:");
            scanf("%d", &actor.def);
            printf("Resistencia:");
            scanf("%d", &actor.res);
            printf("Velociadade:");
            scanf("%d", &actor.spd);
              getchar();
            printf("Nome do Inimigo:");
            scanf("%[^\n]", actor.nome);
            if( Inserir( &enemy, &actor ) ) {
                printf("Inimigo inserido com susesso!\n");
                enemy_number++;
            }
            else{
                printf(REPETIDO);
            }
            break;

          case PROCURAR:
			printf("De que lista você deseja procurar?\n1 - Lista de Hérois\t2 - Lista de Inimigos\n");
            scanf("%d", &type);
            switch( type ){
				case 1:
					printf("Insira o nome do Héroi procrurado:\n");
					scanf("\n%400[^\n]", actor.nome);
					escolhido = Procurar(&hero, &actor);
					if( escolhido != NULL){
						ImprimirElemento( escolhido );
					}else{
						printf("Héroi procurado não encontrado.\n");
					}
					break;

				case 2:
					printf("Insira o nome do Inimigo procrurado:\n");
					scanf("\n%400[^\n]", actor.nome);
					escolhido = Procurar(&enemy, &actor);
					if( escolhido != NULL){
                        ImprimirElemento( escolhido );
					}else{
						printf("Inimigo procurado não encontrado.\n");
					}
					break;
			}
		  break;

          case REMOVER:
			printf("De que lista você deseja remover?\n1 - Lista de Hérois\t2 - Lista de Inimigos\n");
            scanf("%d", &type);
            switch( type ){
				case 1:
					printf("Insira o nome do Héroi a ser removido:\n");
					scanf("\n%400[^\n]", actor.nome);
					if( Remover( &hero, &actor ) ) {
						printf("Héroi removido com sucesso\n");
                        hero_number--;
                    }
                    else
						printf("Nome do Héroi inserido não existe na lista\n");
				break;

				case 2:
					printf("Insira o nome do Inimigo a ser removido:\n");
					scanf("\n%400[^\n]", actor.nome);
					if( Remover( &enemy, &actor ) ) {
                        enemy_number--;
                    	printf("Inimigo removido com sucesso\n");
                    }
                    else
						printf("Nome do Inimigo inserido não existe na lista\n");
				break;
			}
          break;

          case IMPRIMIR:
			printf("Que lista você deseja imprimir?\n0 - Lista de Hérois\t1 - Lista de Inimigos\n");
            scanf("%d", &type);
            if(type)
				Imprimir(&enemy);
			else
				Imprimir(&hero);
          break;

       }
    }

    printf("hero number: %d\n", hero_number );
    printf("enemy number: %d\n", enemy_number );

    // Arquivos
    heroarq = fopen("herobd.dat", "wb");
    enemyarq = fopen("enemybd.dat", "wb");

    fwrite( &hero_number , sizeof(int) , 1 , heroarq );

    fseek( heroarq, sizeof(hero_number), SEEK_CUR );

    _node *paux = hero.inicio;

    if( heroarq != NULL ) {
        while ( paux != NULL ) {
            fwrite( &(paux->actor) , sizeof(ACTOR) , 1 , heroarq );

            fseek( heroarq, sizeof(ACTOR), SEEK_CUR );

            paux = paux->next;
        }
    }

    fwrite( &enemy_number , sizeof(int) , 1 , enemyarq );

    fseek( enemyarq, sizeof(enemy_number), SEEK_CUR );

    paux = enemy.inicio;
    if( enemyarq != NULL ) {
        while ( paux != NULL ) {
            fwrite( &(paux->actor) , sizeof(ACTOR) , 1, enemyarq );

            fseek( enemyarq, sizeof(ACTOR), SEEK_CUR );

            paux = paux->next;
        }
    }

    // ------------------------------------------------------


    // battlestart( &h, &e, hn, en ) ? printf("You Win!\n") : printf("You Lose!\n"); ;

    LiberarLista(&hero);
	LiberarLista(&enemy);
    fclose(heroarq);
    fclose(enemyarq);

    printf("Party inserida!\n");
    return 0;
}

// ----------------------------------------------------------
// Funcao Imprimir: Imprime lista inteira
// ----------------------------------------------------------

void Imprimir( LISTA_LIGADA *l ) {

    if( l->inicio == NULL )
        return;

    _node *p = l->inicio;

    while( p != NULL ) {
        printf("||Name: %s\t\t||\n", p->actor.nome);
        printf("||HP:  %d\t\t||\n", p->actor.hp);
        printf("||STR: %d\t\t||\n", p->actor.str);
        printf("||MAG: %d\t\t||\n", p->actor.mag);
        printf("||DEF: %d\t\t||\n", p->actor.def);
        printf("||RES: %d\t\t||\n", p->actor.res);
        printf("||SPD: %d\t\t||\n\n", p->actor.spd);

        p = p->next;
    }

    printf("\n");
}

void ImprimirElemento(  _node *escolhido  ) {

    if( escolhido == NULL )
        return;

    printf("||Name: %s\t\t||\n", escolhido->actor.nome);
    printf("||HP:  %d\t\t||\n", escolhido->actor.hp);
    printf("||STR: %d\t\t||\n", escolhido->actor.str);
    printf("||MAG: %d\t\t||\n", escolhido->actor.mag);
    printf("||DEF: %d\t\t||\n", escolhido->actor.def);
    printf("||RES: %d\t\t||\n", escolhido->actor.res);
    printf("||SPD: %d\t\t||\n\n", escolhido->actor.spd);

    printf("\n");
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
