#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "lista.h"

// menu de opcoes
#define SAIR 			0
#define INSERIR_HERO	1
#define INSERIR_ENEMY	2
#define PROCURAR		3
#define REMOVER			4
#define IMPRIMIR		5

// constantes
#define MAX     201 //JOOJ

// frases pre-definidas
#define REPETIDO "REPETIDO\n"
#define INEXISTENTE "INEXISTENTE\n"

//REGISTROS

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

// PROTOTIPO DAS FUNCOES
// int battlestart( actor ** h, actor ** e, int hn, int en );
// actor ** turnmaker( actor *headh, actor *heade );
void Imprimir( LISTA_LIGADA *l );

// ROTINA PRINCIPAL

int main() {
    LISTA_LIGADA hero;
    LISTA_LIGADA enemy;
    ACTOR actor;
	_node *escolhido = NULL;

    // Inicializa as listas
    hero.inicio = NULL;
    enemy.inicio = NULL;
    //

    // Arquivos

    //

    int hero_number = 0, enemy_number = 0, type;

    int opt = 1;
    while(opt != 0) {
	   scanf("%d",&opt);
       switch(opt){

          case INSERIR_HERO:
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
					escolhido = Procurar_pelo_nome(&hero, &actor);
					if( escolhido != NULL){
							printf("||Name: %s\t\t||\n", escolhido->actor.nome);
							printf("||HP:  %d\t\t||\n", escolhido->actor.hp);
							printf("||STR: %d\t\t||\n", escolhido->actor.str);
							printf("||MAG: %d\t\t||\n", escolhido->actor.mag);
							printf("||DEF: %d\t\t||\n", escolhido->actor.def);
							printf("||RES: %d\t\t||\n", escolhido->actor.res);
							printf("||SPD: %d\t\t||\n\n", escolhido->actor.spd);
					}else{
						printf("Héroi procurado não encontrado.\n");
					}
					break;

				case 2:
					printf("Insira o nome do Inimigo procrurado:\n");
					scanf("\n%400[^\n]", actor.nome);
					escolhido = Procurar_pelo_nome(&enemy, &actor);
					if( escolhido != NULL){
							printf("||Name: %s\t\t||\n", escolhido->actor.nome);
							printf("||HP:  %d\t\t||\n", escolhido->actor.hp);
							printf("||STR: %d\t\t||\n", escolhido->actor.str);
							printf("||MAG: %d\t\t||\n", escolhido->actor.mag);
							printf("||DEF: %d\t\t||\n", escolhido->actor.def);
							printf("||RES: %d\t\t||\n", escolhido->actor.res);
							printf("||SPD: %d\t\t||\n\n", escolhido->actor.spd);
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
					if( Remover( &hero, &actor ) )
						printf("Héroi removido com sucesso\n");
					else
						printf("Nome do Héroi inserido não existe na lista\n");
				break;

				case 2:
					printf("Insira o nome do Inimigo a ser removido:\n");
					scanf("\n%400[^\n]", actor.nome);
					if( Remover( &enemy, &actor ) )
						printf("Inimigo removido com sucesso\n");
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
	libera_lista(&hero);
	libera_lista(&enemy);
    printf("Party inserida!\n");

    // battlestart( &h, &e, hn, en ) ? printf("You Win!\n") : printf("You Lose!\n"); ;

    return 0;
}

//imprime os elementos da lista
// void Imprimir( actor** l ) {
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
