#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
typedef struct _node{
    struct _node *next;
    int hp, str, mag, def, res, spd, sts;	//sts 
    int turndefend = 0;
    char nome[MAX];
}actor;

// PROTOTIPO DAS FUNCOES
// int battlestart( actor ** h, actor ** e, int hn, int en );
// actor ** turnmaker( actor *headh, actor *heade );
int Inserir( actor ** l, int HP, int STR, int MAG, int DEF, int RES, int SPD, char NOME[] );
void InserirCampos( actor *p, int HP, int STR, int MAG, int DEF, int RES, int SPD, char NOME[] );
actor *Procurar_pelo_nome( actor ** l, char NOME[] );
int Remover( actor ** l, char NOME[] );
void Imprimir( actor** l );
void libera_lista( actor **primeiro );
actor *turn_maker ( actor **hero, actor **enemy );
actor *listade_batalha (actor **lista );

// ROTINA PRINCIPAL

int main() {
    actor *hero = NULL;
    actor *enemy = NULL;
	actor *escolhido;

    int HP, STR, MAG, DEF, RES, SPD, type, hero_number = 0, enemy_number = 0;
    char NAME[MAX];

    int opt = 1;
    while(opt != 0) {
		scanf("%d",&opt);
       switch(opt){

          case INSERIR_HERO:
            printf("Insira os seguintes dados:\n");
			printf("HP:");
            scanf("%d", &HP);
            printf("Força:");
            scanf("%d", &STR);
            printf("Magia:");
            scanf("%d", &MAG);
            printf("Defesa:");
            scanf("%d", &DEF);
            printf("Resistencia:");
            scanf("%d", &RES);
            printf("Velociadade:");
            scanf("%d", &SPD);
            getchar();
            printf("Nome do Héroi:");
            scanf("%[^\n]", NAME);
            if( Inserir( &hero, HP, STR, MAG, DEF, RES, SPD, NAME ) ) {
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
            scanf("%d", &HP);
            printf("Força:");
            scanf("%d", &STR);
            printf("Magia:");
            scanf("%d", &MAG);
            printf("Defesa:");
            scanf("%d", &DEF);
            printf("Resistencia:");
            scanf("%d", &RES);
            printf("Velociadade:");
            scanf("%d", &SPD);
            getchar();
            printf("Nome do Inimigo:");
            scanf("%[^\n]", NAME);
            if( Inserir( &enemy, HP, STR, MAG, DEF, RES, SPD, NAME ) ) {
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
					scanf("\n%400[^\n]", NAME);
					escolhido = Procurar_pelo_nome(&hero, NAME);
					if( escolhido != NULL){
							printf("||Name: %s\t\t||\n", escolhido->nome);
							printf("||HP:  %d\t\t||\n", escolhido->hp);
							printf("||STR: %d\t\t||\n", escolhido->str);
							printf("||MAG: %d\t\t||\n", escolhido->mag);
							printf("||DEF: %d\t\t||\n", escolhido->def);
							printf("||RES: %d\t\t||\n", escolhido->res);
							printf("||SPD: %d\t\t||\n\n", escolhido->spd);
					}else{
						printf("Héroi procurado não encontrado.\n");
					}
					break;
				
				case 2:
					printf("Insira o nome do Inimigo procrurado:\n");
					scanf("\n%400[^\n]", NAME);
					escolhido = Procurar_pelo_nome(&hero, NAME);
					if( escolhido != NULL){
							printf("||Name: %s\t\t||\n", escolhido->nome);
							printf("||HP:  %d\t\t||\n", escolhido->hp);
							printf("||STR: %d\t\t||\n", escolhido->str);
							printf("||MAG: %d\t\t||\n", escolhido->mag);
							printf("||DEF: %d\t\t||\n", escolhido->def);
							printf("||RES: %d\t\t||\n", escolhido->res);
							printf("||SPD: %d\t\t||\n\n", escolhido->spd);
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
					scanf("\n%400[^\n]", NAME);
					if( Remover( &hero, NAME ) )
						printf("Héroi removido com sucesso\n");
					else
						printf("Nome do Héroi inserido não existe na lista\n");
				break;
					
				case 2:
					printf("Insira o nome do Inimigo a ser removido:\n");
					scanf("\n%400[^\n]", NAME);
					if( Remover( &enemy, NAME ) )
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


//função que coloca os elementos no no da lista
void InserirCampos( actor *p, int HP, int STR, int MAG, int DEF, int RES, int SPD, char NOME[] ) {
    p->hp = HP;
    p->str = STR;
    p->mag = MAG;
    p->def = DEF;
    p->res = RES;
    p->spd = SPD;
    strcpy(p->nome, NOME);
}

// insere o elemento no fianl da lista, retorna:
//	0 o elemento for repetido
//	1 se o elemento for inserido com sucesso
int Inserir( actor **l, int HP, int STR, int MAG, int DEF, int RES, int SPD, char NOME[] ) {

    if( *l == NULL ) {
        actor *p = (actor*)malloc(sizeof(actor));

        InserirCampos( p, HP, STR, MAG, DEF, RES, SPD, NOME );

        *l = p;
        p->next = NULL;

        return 1;
    }
    else {
        actor *p = *l;

        while ( 1 ) {
            if ( strcmp(NOME, p->nome) == 0  )
                return 0;

            else if( p->next == NULL ){
                actor *new = (actor*)malloc(sizeof(actor));

                InserirCampos( new, HP, STR, MAG, DEF, RES, SPD, NOME );

                p->next = new;
                new->next = NULL;
                return 1;
            }
            p = p->next;
        }

    }

}

// imprime na tela os RAs de todos os alunos com o nome procurado, ou imprime INEXISTENTE
// Retorna o ponteriro do nome procurado se encontrado, ou NULL se inexistente ou não encontrado,
actor *Procurar_pelo_nome( actor ** l, char NOME[] ) {

    if( *l == NULL )
        return NULL;

    actor *p = *l;
    
    while( p != NULL ) {
        if( strcmp(NOME, p->nome) == 0 ) {
            return p;
        }
        p = p->next;
    }

    return NULL;
}

//função que remove um elemento da lista com o nome listado, retorna:
//	0 caso o elemento não existe
//	1 caso o elemnto foi removido com sucesso
int Remover( actor ** l, char NOME[] ) {
	actor *anterior = *l;
	
	if( anterior == NULL )
		return 0;
	
	if( strcmp(NOME, anterior->nome ) == 0 ){
		free(anterior);
		*l = NULL;
		return 1;
	}
	
	actor *atual = anterior->next;
	
	while(atual != NULL){
		if( strcmp(NOME, atual->nome ) == 0){
			anterior->next = atual->next;
			free(atual);
			return 1;
		}
		atual = atual->next;
		anterior = anterior->next;
	}
	return 0;

}

actor *listade_batalha ( actor **l, char NOME[] ){
	actor *p = *l;
	while( p != NULL ){
		if( strcmp(NOME, atual->nome ) == 0 ){
			return 
		}
		p = p->next;
	}
}

actor *turn_maker ( actor **hero, actor **enemy ){
	
}

//imprime os elementos da lista
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

void libera_lista(actor **primeiro){//limpa a lista, deixando o espaço de memória que ela ocupava vazio
	actor *anterior = *primeiro;
	if(anterior == NULL){	//se a lista estiver vazia, a função nao faz nada
	}else{
		actor *atual = anterior->next;
		if(atual == NULL){	//caso o valor atual seja o unico da lista, ele é liberando
			free(anterior);
		}else{
			while (atual != NULL){		//enquando existir algum elemento da lista, o loop vai liberando um por um os nós da lista
				free(anterior);
				*primeiro = atual;
				anterior = atual;
				atual = anterior->next;
			}
			free(anterior);
		}
	}
}


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
