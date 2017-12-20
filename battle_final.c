#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ----------------------------------------------------------
// Bibliotecas internas
// ----------------------------------------------------------
#include "lista.h"
#include "arquivo.h"

// ----------------------------------------------------------
// Opcoes do Menu
// ----------------------------------------------------------
#define SAIR 						0	//!< Opção de sair do programa.
#define INSERIR_HERO_ENEMY			1	//!< Opção de inserir herói ou inimigo.
#define PROCURAR					2	//!< Opção de procurar pelo nome um herói ou inimigo.
#define REMOVER						3	//!< Opção de remover um herói ou inimigo.
#define IMPRIMIR					4	//!< Opção de imprimir elementos de uma lista.
#define INSERIR_HERO_ENEMY_BATTLE	5	//!< Opção de inserir elementos na lista de batalha.
#define INICIAR_BATALHA				6	//!< Opção de iniciar batalha.
#define IMPORTARCSV  			    7	//!< Opção de importar para arquivo .csv
#define EXPORTARCSV        			8	//!< Opção de exportar para arquivo .csv

// ----------------------------------------------------------
// Constantes
// ----------------------------------------------------------

#define MAX     201 //!< Número máximo de caractéres em nomes.

// ----------------------------------------------------------
// Prototipo das funcoes
// ----------------------------------------------------------
void Imprimir( LISTA_LIGADA *l );
void ImprimirElemento( _node *escolhido );

void TurnMaker ( LISTA_LIGADA *h, LISTA_LIGADA *e, LISTA_LIGADA *battle );
int FazerLista( LISTA_LIGADA *escolhido, LISTA_LIGADA *l, ACTOR *procurado );
int ChecarLista( LISTA_LIGADA *l );
void Battle( LISTA_LIGADA *battle_lista, LISTA_LIGADA *hero, LISTA_LIGADA *enemy, int hero_battle_num, int enemy_battle_num );
void RemoverBattle( LISTA_LIGADA *l, ACTOR *actor );
void LiberarListaLigada( LISTA_LIGADA *l );
void MostrarHP( LISTA_LIGADA *battle, LISTA_LIGADA *enemy, LISTA_LIGADA *hero );
int AcertoFisico( _node *atacante );
int AcertoMagico( _node *atacante );

// ----------------------------------------------------------
// Rotina Principal
// ----------------------------------------------------------
int main() {
    //Declaração das listas
    LISTA_LIGADA hero;
    LISTA_LIGADA enemy;
    LISTA_LIGADA battle_hero;
    LISTA_LIGADA battle_enemy;
    LISTA_LIGADA battle_list;

    //Auxiliar
    ACTOR actor;
	_node *escolhido = NULL;

	//Constantes
    int hero_number = 0, enemy_number = 0, type, auxiliar;
    int hero_battle_number = 0, enemy_battle_number = 0;
    int opt, aux;

    // Inicializa as listas
    hero.inicio = NULL;
    enemy.inicio = NULL;
    battle_hero.inicio = NULL;
    battle_enemy.inicio = NULL;
    // ------------------------------------------------------

    system("clear");

	//Tela de Inicio
	while( opt != 1){
		printf(R"EOF(
  ____ ____  _   _ _   _ ____  _     _____    ___  _   _ _____ ____ _____
 / ___|  _ \| | | | \ | |  _ \| |   | ____|  / _ \| | | | ____/ ___|_   _|
| |   | |_) | | | |  \| | | | | |   |  _|   | | | | | | |  _| \___ \ | |
| |___|  _ <| |_| | |\  | |_| | |___| |___  | |_| | |_| | |___ ___) || |
 \____|_| \_\\___/|_| \_|____/|_____|_____|  \__\_\\___/|_____|____/ |_|


                              __     __
                              \ \   / /
                               \ \ / /
                                \ V /
                                 \_/
	)EOF");

		printf(R"EOF(
  _____ _  _ ___    ___ _____   _____ _____ _   _    ___    ___  ___
 |_   _| || | __|  / __| _ \ \ / / __|_   _/_\ | |  / __|  / _ \| __|
   | | | __ | _|  | (__|   /\ V /\__ \ | |/ _ \| |__\__ \ | (_) | _|
   |_| |_||_|___|_ \___|_|_\ |_| |___/_|_/_/_\_\____|___/_ \___/|_|
           ___ ___ _  _  ___ _    ___ ___   ___   ___  ___
          / __|_ _| \| |/ __| |  | __|   \ / _ \ / _ \| __|
         | (_ || || .` | (_ | |__| _|| |) | (_) | (_) | _|
          \___|___|_|\_|\___|____|___|___/ \___/ \___/|_|
	)EOF");
		printf("\n0 - Sair\n");
		printf("1 - Começar!\n");
		printf("2 - Como jogar\n");
		printf("3 - Créditos\n");
		scanf("%d", &opt);

		switch( opt ){
		case 0:
			printf("Tem certeza que deseja sair?\n 1 - Sim\n 2 - Não\n");
			scanf("%d", &aux);
			if( aux == 1 )
				return 0;
			printf("\n");
		break;

		case 2:
			printf("Bem vindo aventureiro a Crundle Quest V! The Crystals of Gingledoof!\n");
			printf("Crundle Quest V é um sistema de batalha criado por André Bariani e Giovanni Rossi\n");
			printf("como uma homenagem aos antigos RPG's.\n");
			printf("Como Jogar:\n");
			printf("O jogo consiste em dois times (um de Heróis e outro de Inimigos) que vão a batalha.\n");
			printf("Vence o time que derrotar todos os opontes do time adversário! Você vai controlar o\n");
			printf("time dos Heróis, e o computador controla os inimigos. Para começar, você prescisa cri-\n");
			printf("ar Heróis e Inimigos que serão inseridos na lista principal e mandar quantos Inimigos e\n");
			printf("Heróis você achar nescessário para a batalha. Depois basta começar a batalha! E que o\n");
			printf("melhor time vença!\n");
			printf("Pressione um número qualquer e a tecla enter para voltar\n");
			scanf("%d", &aux);
			printf("\n");
		break;

		case 3:
			printf("Créditos:\nAndré Matheus Bariani Trava\tRA - 743506\nResponsável por:\n");
			printf("-Documentação do código\n-Implementação de arquivos\n-Implementação de listas simples\n-Correção de bugs\n-Testes\n");
			printf("\nGiovanni Marçon Rossi\tRA - 743541\nResponsável por:\n");
			printf("-Implementação do sistema de batalha\n-Implementação da lista circular com sentinela\n-Documentação em pdf\n-Correção de bugs\n-Testes");
			printf(R"EOF(
        ^
        $
        |
     _, | O
   ,'*\ o=Y)       		      o   o
   `'\ `-</--_     		      |\O/|
      `. _\  /!    	 	       \Y/
       H`**'H      	 	       /_\
       H    H      	 	       _W_
  Great Sir. Bariani	 and   Great Wizard Giovanni
Riding His loyal horse!       casting a powerful spell!
	)EOF");
			printf("Pressione um número qualquer e a tecla enter para voltar\n");
			scanf("%d", &aux);
			printf("\n");
		break;

		}
	}
	// ------------------------------------------------------

    // Arquivos
    FILE *heroarq;
    FILE *enemyarq;

    heroarq = fopen("herobd.dat", "rb");
    enemyarq = fopen("enemybd.dat", "rb");

    hero.inicio = ImportarArquivo( heroarq, &hero, &hero_number);
    enemy.inicio = ImportarArquivo( enemyarq, &enemy, &enemy_number);
    // ------------------------------------------------------

    while(opt != 0) {
       printf("--------------------------------------------");
	   printf("\nMenu de opções:\n");
	   printf("1 - Inserir um Herói/Inimigo\n");
	   printf("2 - Procurar por um Herói/Inimigo\n");
	   printf("3 - Remover um Herói/Inimigo\n");
	   printf("4 - Mostrar a lista de Heróis/Inimigos\n");
	   printf("5 - Inserir um Herói/Inimigo para a batalha\n");
	   printf("6 - Começar a Batalha!\n");
	   printf("7 - Importar uma das listas em CSV\n");
	   printf("8 - Exportar uma das listas em CSV\n");
	   printf("0 - Sair\n");
       printf("--------------------------------------------\n");
	   scanf("%d",&opt);
       switch(opt) {

          case INSERIR_HERO_ENEMY:
            system("clear");
            printf("\nO que você deseja inserir?\n1 - Herói\t 2 - Inimigo\n");
            scanf("%d", &aux);
            aux--;
            if( aux ){
				printf("\nInsira os seguintes dados:\n");
				printf("HP:");
				scanf("%d", &actor.hp);
				printf("Força:");
				scanf("%d", &actor.str);
				printf("Magia:");
				scanf("%d", &actor.mag);
				printf("Defesa:");
				scanf("%d", &actor.def);
				printf("Acerto:");
				scanf("%d", &actor.acc);
				printf("Velocidade:");
				scanf("%d", &actor.spd);
				  getchar();
				printf("Nome do Inimigo:");
				scanf("%[^\n]", actor.nome);
				actor.sts = 1;
				actor.turndefend = 0;
				enemy_number++;
				if( Inserir( &enemy, &actor ) )
					printf("\nInimigo inserido com susesso!\n");
				else
					printf("\nInimigo repetido\n");
			}else{
				printf("\nInsira os seguintes dados:\n");
				printf("HP:");
				scanf("%d", &actor.hp);
				printf("Força:");
				scanf("%d", &actor.str);
				printf("Magia:");
				scanf("%d", &actor.mag);
				printf("Defesa:");
				scanf("%d", &actor.def);
				printf("Acerto:");
				scanf("%d", &actor.acc);
				printf("Velocidade:");
				scanf("%d", &actor.spd);
				getchar();
				printf("Nome do Herói:");
				scanf("%[^\n]", actor.nome);
				actor.sts = 0;
				actor.turndefend = 0;
				hero_number++;
				if( Inserir( &hero, &actor ) )
					printf("\nHerói inserido com susesso!\n");
				else
					printf("\nHerói repetido\n");
			}
          break;

          case PROCURAR:
            system("clear");
			printf("\nDe que lista você deseja procurar?\n1 - Lista de Heróis\t2 - Lista de Inimigos\n");
            scanf("%d", &type);
            type--;
            if( type ){
				printf("\nInsira o nome do Inimigo procrurado:\n");
				scanf("\n%400[^\n]", actor.nome);
				escolhido = Procurar(&enemy, &actor);
				if( escolhido != NULL){
				   printf("\nInimigo encontrado:\n");
                   ImprimirElemento( escolhido );
				}else
				   printf("\nInimigo procurado não encontrado.\n");
			}else{
				printf("\nInsira o nome do Herói procrurado:\n");
				scanf("\n%400[^\n]", actor.nome);
				escolhido = Procurar(&hero, &actor);
				if( escolhido != NULL){
				   printf("\nHerói encontrado:\n");
				   ImprimirElemento( escolhido );
				}else
				   printf("\nHéroi procurado não encontrado.\n");
			}
		    break;

          case REMOVER:
            system("clear");
			printf("\nDe que lista você deseja remover?\n1 - Lista de Heróis\t2 - Lista de Inimigos\n");
            scanf("%d", &type);
            type--;
            if( type ){
				printf("\nInsira o nome do Inimigo a ser removido:\n");
				scanf("\n%400[^\n]", actor.nome);
				if( Remover( &enemy, &actor ) ) {
					printf("\nInimigo removido com sucesso\n");
                    enemy_number--;
                }
				else
					printf("\nNome do Inimigo inserido não existe na lista\n");
			}else{
				printf("\nInsira o nome do Herói a ser removido:\n");
				scanf("\n%400[^\n]", actor.nome);
				if( Remover( &hero, &actor ) ) {
					printf("\nHerói removido com sucesso\n");
                    hero_number--;
                }
				else
					printf("\nNome do Herói inserido não existe na lista\n");
			}
            break;

          case IMPRIMIR:
            system("clear");
			printf("\nQue lista você deseja imprimir?\n1 - Lista de Heróis\t2 - Lista de Inimigos\n3 - Lista de Heróis que vão à batalha\n4 - Lista de Inimigos que vão à batalha\n");
            type = 0;
            while( 1 ){
				scanf("%d", &type);
				if( type == 1 || type == 2 || type == 3 || type == 4 )
					break;
				else
					printf("\nPor favor insira um número válido\n");
			}
				switch( type ){
					case 1:
						Imprimir( &hero );
					break;

					case 2:
						Imprimir( &enemy );
					break;

					case 3:
						Imprimir( &battle_hero );
					break;

					case 4:
						Imprimir( &battle_enemy );
					break;

					default:
						printf("\nPor favor insira um número válido\n");
					break;
				}
          break;

          case INSERIR_HERO_ENEMY_BATTLE:
            system("clear");
			printf("\nQuem você deseja mandar para a batalha?\n1 - Herói\t2 - Inimigo\n");
			scanf("%d", &type);
			type--;
			if( type ){
                Imprimir( &enemy );
				printf("\nInsira o nome do Inimigo que vai para a batalha:\n");
				scanf("\n%400[^\n]", actor.nome);
				auxiliar = FazerLista( &enemy, &battle_enemy, &actor );
					if( auxiliar == 1 ){
						printf("\nInimigo inserido para a batalha!\n");
						enemy_battle_number++;
					}
					else if( auxiliar == 0 )
						printf("\nInimigo não encontrado\n");
					else
						printf("\nInimigo repetido\n");
			}else{
                Imprimir( &hero );
                printf("\nInsira o nome do Herói que vai para a batalha:\n");
				scanf("\n%400[^\n]", actor.nome);
				auxiliar = FazerLista( &hero, &battle_hero, &actor );
					if( auxiliar == 1 ){
						printf("\nHerói inserido para a batalha!\n");
						hero_battle_number++;
					}
					else if( auxiliar == 0 )
						printf("\nHerói não encontrado\n");
					else
						printf("\nHerói repetido\n");
			}
		  break;

		  case INICIAR_BATALHA:		//COLOCAR UM AVISINHO NO FINAL, FALANDO QUE A LISTA DO HEROIS E INIMIGOS QUE VAO A BATALHA FOI EXCLUIDA, SE O USUARIO QUISER BATALHAR DE NOVO ELE PRESCISA INSERIR OS HEROIS NOVAMENTE PARA A BATALHA
		    if( ChecarLista( &battle_hero ) != 1 ){
				printf("\nLista de Heróis vazia, por fazor insira pelo menos 1 Herói na lista\n");
			}else{
				if( ChecarLista( &battle_enemy ) != 1 ){
					printf("\nLista de Inimigos vazia, por fazor insira pelo menos 1 Inimigo na lista\n");
				}else{
                    system("clear");
					TurnMaker( &battle_hero, &battle_enemy, &battle_list);
					Battle( &battle_list, &battle_hero, &battle_enemy, hero_battle_number, enemy_battle_number );
					LiberarListaLigada( &battle_list );
					LiberarLista( &battle_hero );
					LiberarLista( &battle_enemy );
				}
			}
		  break;

          case IMPORTARCSV:
            system("clear");
            printf("\nImportar para qual lista?\n1 - Lista de Hérois\t2 - Lista de Inimigos\n");
            while ( 1 ){
				scanf("%d", &type);
				type--;
				if( type == 1 || type == 0 )
					break;
				else
					printf("\nPor favor insira um número válido");
			}

			if( type ){
				printf("\nImportar arquivo CSV vai excluir os dados atuais. Continuar?\t1 - Sim\t 0 - Não\n");
                scanf("%d", &type);
                if(type) {
                    char nomearq[MAX];

                    printf("\nInsira nome do arquivo .csv (INSIRA NO FINAL .csv)\n");
                    getchar();
                    scanf("%400[^\n]", nomearq);

                    FILE *imparq;

                    imparq = fopen( nomearq, "r" );

                    if(imparq == NULL) {
                        printf("\nArquivo nao encontrado!\n");
                        break;
                    }

                    LiberarLista( &enemy );

                    enemy.inicio = ImportarCSV( imparq , &enemy_number , 1);

                    fclose( imparq );
                    printf("\n%d inimigos adicionados!\n", enemy_number);
				}
			}else{
				printf("\nImportar arquivo CSV vai excluir os dados atuais. Continuar?\t1 - Sim\t 0 - Não\n");
                scanf("%d", &type);
                if(type) {
                    char nomearq[MAX];

                    printf("\nInsira nome do arquivo .csv (INSIRA NO FINAL .csv)\n");
                    getchar();
                    scanf("%400[^\n]", nomearq);

                    FILE *imparq;

                    imparq = fopen( nomearq, "r" );

                    if(imparq == NULL) {
                        printf("\nArquivo nao encontrado!\n");
                        break;
                    }

                    LiberarLista( &hero );

                    hero.inicio = ImportarCSV( imparq , &hero_number , 0);

                    fclose( imparq );
                    printf("\n%d herois adicionados!\n", hero_number);
                }
			}
          break;

          case EXPORTARCSV:
            system("clear");
            printf("\nExportar para qual lista?\n1 - Lista de Hérois\t2 - Lista de Inimigos\n");

            char nomearq[MAX];
            FILE *exparq;

			while ( 1 ){
				scanf("%d", &type);
				type--;
				if( type == 1 || type == 0 )
					break;
				else
					printf("\nPor favor insira um número válido");
			}

			if( type ){
				printf("\nInsira nome para o arquivo .csv (INSIRA NO FINAL .csv)\n");
                getchar();
                scanf("%400[^\n]", nomearq);

                exparq = fopen(nomearq, "w");

                ExportarCSV( exparq , &enemy );

                fclose(exparq);
			}else{
			    printf("\nInsira nome para o arquivo .csv (INSIRA NO FINAL .csv)\n");
                getchar();
                scanf("%400[^\n]", nomearq);

                exparq = fopen(nomearq, "w");

                ExportarCSV( exparq , &hero );

                fclose(exparq);
			}
          break;

          case SAIR:
			printf("\nTem certeza que deseja sair?\n1 - Sim\t2 - Não\n");
			while( 1 ){
				scanf("%d", &opt);
				if(opt == 1 || opt == 2)
					break;
				else
					printf("\nPor favor insira um número válido\n");
			}
			opt--;
			if( opt )
				opt = 1;
			else
				opt = 0;

          break;

          default:
			printf("\nPor favor insira um número válido\n");
		  break;
       }
    }

    // Arquivos
    heroarq = fopen("herobd.dat", "wb");
    enemyarq = fopen("enemybd.dat", "wb");

    ExportarArquivo( heroarq, &hero, hero_number);
    ExportarArquivo( enemyarq, &enemy, enemy_number);
    // ------------------------------------------------------
	if( battle_hero.inicio != NULL )
		LiberarLista( &battle_hero );

	if( battle_enemy.inicio != NULL )
		LiberarLista( &battle_enemy );

    LiberarLista( &hero );
	LiberarLista( &enemy );
    fclose(heroarq);
    fclose(enemyarq);

    printf("Obrigado por jogar!\n");
    return 0;
}

// ----------------------------------------------------------
/**
 * @brief Imprime a lista escolhida na tela
 *
 * Recebe endereço de lista.
 */
 // ----------------------------------------------------------
void Imprimir( LISTA_LIGADA *l ) {

    if( l->inicio == NULL ){
		printf("\nEsta lista está vazia\n");
        return;
	}

    _node *p = l->inicio;

    while( p != NULL ) {
        printf("||Name: %s\t\t||\n", p->actor.nome);
        printf("||HP:  %d\t\t||\n", p->actor.hp);
        printf("||STR: %d\t\t||\n", p->actor.str);
        printf("||MAG: %d\t\t||\n", p->actor.mag);
        printf("||DEF: %d\t\t||\n", p->actor.def);
        printf("||ACC: %d\t\t||\n", p->actor.acc);
        printf("||SPD: %d\t\t||\n\n", p->actor.spd);

        p = p->next;
    }

    printf("\n");
}

// ----------------------------------------------------------
/**
 * @brief Imprime o elemento escolhido na tela
 *
 * Recebe endereço de um nó.
 */
 // ----------------------------------------------------------
void ImprimirElemento(  _node *escolhido  ) {

    if( escolhido == NULL )
        return;

    printf("||Name: %s\t\t||\n", escolhido->actor.nome);
    printf("||HP:  %d\t\t||\n", escolhido->actor.hp);
    printf("||STR: %d\t\t||\n", escolhido->actor.str);
    printf("||MAG: %d\t\t||\n", escolhido->actor.mag);
    printf("||DEF: %d\t\t||\n", escolhido->actor.def);
    printf("||ACC: %d\t\t||\n", escolhido->actor.acc);
    printf("||SPD: %d\t\t||\n\n", escolhido->actor.spd);

    printf("\n");
}

// ----------------------------------------------------------
/**
 * @brief Insere um certo elemento em uma lista ligada simples normal
 *
 * Recebe endereço de lista onde o elemento está, endereço de lista que será criada, endereço do elemento procurado;
 * Retorna 0 caso o elemento a ser inserido não seja encontrado, 1 caso o elemento seja inserido com sucesso, 2 caso o elemento a ser inserido seja repetido.
 */
 // ----------------------------------------------------------
int FazerLista( LISTA_LIGADA *escolhido, LISTA_LIGADA *l, ACTOR *procurado ){
	_node *paux;
	paux = Procurar( escolhido, procurado );
	if( paux != NULL ){
		if( Inserir( l, &paux->actor ) )
			return 1;
		else
			return 2;
	}else
		return 0;
}

// ----------------------------------------------------------
/**
 * @brief Checa se a lista possui algum elemento
 *
 * Recebe endereço de lista;
 * Retorna 0 se a lista não possui nenhum elemento, 1 se a lista tem mais de 1 elemento.
 */
 // ----------------------------------------------------------
int ChecarLista( LISTA_LIGADA *l ){
	if( l->inicio != NULL )
		return 1;
	else
		return 0;
}

// ----------------------------------------------------------
/**
 * @brief Cria a lista ligada circular com sentinela, que será usada na batalha
 *
 * Recebe endereço de uma lista contendo herois, endereço de uma lista contendo inimigos, endereço de lista ligada circular com sentinela;
 */
 // ----------------------------------------------------------
void TurnMaker ( LISTA_LIGADA *h, LISTA_LIGADA *e, LISTA_LIGADA *battle ){
		//flag
	int flag = 0;
		//Ponteiros
	_node *anterior;
	_node *atual;
	_node *hero = h->inicio;
	_node *enemy = e->inicio;

		//Criando o sentinela
	_node *sentinela = (_node*)malloc(sizeof(_node));
	sentinela->next = sentinela;
	sentinela->actor.spd = 1000;
	sentinela->actor.sts = 2;
	battle->inicio = sentinela;

	while( hero != NULL ){		//Inserindo Herois
		_node *new = (_node*)malloc(sizeof(_node));
		if( flag == 0 ){
			sentinela->next = new;
			new->next = sentinela;
			new->actor = hero->actor;
			flag++;
		}else{
			anterior = sentinela;
			atual = anterior->next;
			while( atual != sentinela ){
				if( hero->actor.spd >= atual->actor.spd ){
					anterior->next = new;
					new->next = atual;
					new->actor = hero->actor;
					break;
				}else{
					if( atual->next == sentinela ){
						atual->next = new;
						new->next = sentinela;
						new->actor = hero->actor;
						atual = atual->next;
						break;
					}
				}
				anterior = anterior->next;
				atual = atual->next;
			}
		}
		hero = hero->next;
	}

	while( enemy != NULL ){		//Inserindo inimigos
		_node *new = (_node*)malloc(sizeof(_node));
		anterior = sentinela;
		atual = anterior->next;
		while( atual != sentinela ){
			if( enemy->actor.spd >= atual->actor.spd ){
				anterior->next = new;
				new->next = atual;
				new->actor = enemy->actor;
				break;
			}else{
				if( atual->next == sentinela ){
					atual->next = new;
					new->next = sentinela;
					new->actor = enemy->actor;
					atual = atual->next;
					break;
				}
			}
			anterior = anterior->next;
			atual = atual->next;
		}
		enemy = enemy->next;
	}
}

// ----------------------------------------------------------
/**
 * @brief Função que faz a batalha acontecer dado os inimigos e herois disponíveis
 *
 * Recebe endereço de lista ligada circular com sentinela, endereço de lista ligada contendo heróis, endereço de lista ligada contendo inimigos, quantidade de herois que vão a batalha, quantidade de inimigos que vão a batalha;
 */
 // ----------------------------------------------------------
void Battle( LISTA_LIGADA *battle_lista, LISTA_LIGADA *hero, LISTA_LIGADA *enemy, int hero_battle_num, int enemy_battle_num ){
		//Ponteiros
	_node *atual_hero = hero->inicio;
	_node *atual_enemy = enemy->inicio;
	_node *atual_battle = battle_lista->inicio->next;
	_node *paux;
		//Flags
	int flag = 0, morte = 0;
		//Opçoes	/Constantes
	int action, attack, num = 1, sucess;

	while ( 1 ){
		if( atual_battle->actor.sts != 2 ){							//checa se é sentinela
			if( atual_battle->actor.sts == 0 ){						//hero turn
				while ( flag != 1 ){								//Opções do jogador, sai do loop quando a ação escolhida é realizada
					MostrarHP( battle_lista, enemy, hero );
					printf("\nO que %s vai fazer?\n1 - Atacar com arma\n2 - Atacar com magia\n3 - Defender\n", atual_battle->actor.nome);
					paux = Procurar( hero, &atual_battle->actor );
					paux->actor.turndefend = 0;
					atual_enemy = enemy->inicio;
					scanf("%d", &action);
                    system("clear");
					switch( action ){
						case 1:
							printf("Quem você deseja atacar?\n0 - Voltar\n");

							while( atual_enemy != NULL ){			//mostra a lista de inimigos para atacar
								printf("%d - %s\n", num, atual_enemy->actor.nome);
								atual_enemy = atual_enemy->next;
								num++;
							}

							num = 1;
							atual_enemy = enemy->inicio;

							while ( 1 ){							//checa se o valor inserido pelo jogador é válido
								scanf("%d", &attack);
								if( attack <= enemy_battle_num && attack > -1 )
									break;
								else
									printf("\nPor favor insira um número válido\n");
							}

							if( attack == 0 )						//condição para voltar as ações
								break;

							for( int i = 1; i < attack; i++ ){
								atual_enemy = atual_enemy->next;
							}

							if( atual_enemy->actor.turndefend ){	//checa se o alvo está defendendo
								sucess = AcertoFisico( atual_battle );
								if( sucess ){						//checa se o atacante acerta
									atual_enemy->actor.hp = atual_enemy->actor.hp - (atual_battle->actor.str+1)/2;
                                    printf("--------------------------------------------\n");
									printf("\n%s ataca, %s se defende e leva %d de dano!\n", atual_battle->actor.nome, atual_enemy->actor.nome, (atual_battle->actor.str+1)/2);
								}else {
                                    printf("--------------------------------------------\n");
									printf("\n%s ataca mas erra!\n", atual_battle->actor.nome);
                                }
							}else{
								sucess = AcertoFisico( atual_battle );
								if( sucess ){						//checa se o atacante acerta
									atual_enemy->actor.hp = atual_enemy->actor.hp - atual_battle->actor.str;
                                    printf("--------------------------------------------\n");
									printf("\n%s ataca e %s leva %d de dano!\n", atual_battle->actor.nome, atual_enemy->actor.nome, atual_battle->actor.str);
								}else {
                                    printf("--------------------------------------------\n");
									printf("\n%s ataca mas erra!\n", atual_battle->actor.nome);
                                }
							}

							if( atual_enemy->actor.hp <= 0 )		//checa se o alvo está morto ou não
								morte++;

							flag++;
						break;

						case 2:
							printf("\nQuem você deseja atacar?\n0 - Voltar\n");

							while( atual_enemy != NULL ){			//mostra a lista de inimigos para atacar
								printf("%d - %s\n", num, atual_enemy->actor.nome);
								atual_enemy = atual_enemy->next;
								num++;
							}

							num = 1;
							atual_enemy = enemy->inicio;

							while ( 1 ){							//checa se o valor inserido pelo jogador é válido
								scanf("%d", &attack);
								if( attack <= enemy_battle_num && attack > -1 )
									break;
								else
									printf("\nPor favor insira um número válido\n");
							}

							if( attack == 0 )						//condição para voltar as ações
								break;

							for( int i = 1; i < attack; i++ ){
								atual_enemy = atual_enemy->next;
							}

							sucess = AcertoMagico( atual_battle );
							if( sucess ){							//checa se o atacante acertou
								atual_enemy->actor.hp = atual_enemy->actor.hp - atual_battle->actor.mag;
                                printf("--------------------------------------------\n");
								printf("\n%s ataca com magia e %s leva %d de dano!\n", atual_battle->actor.nome, atual_enemy->actor.nome, atual_battle->actor.mag);
							}else {
                                printf("--------------------------------------------\n");
								printf("\n%s ataca mas erra!\n", atual_battle->actor.nome);
                            }
							if( atual_enemy->actor.hp <= 0 )		//checa se o alvo está morto ou não
								morte++;

							flag++;
						break;

						case 3:										//caso o heroi escolha se defender
                            printf("--------------------------------------------\n");
                            printf("\n%s esta se defendendo!\n", atual_battle->actor.nome);
							paux = Procurar( hero, &atual_battle->actor );
							paux->actor.turndefend = 1;

							flag++;
						break;

						default :
						printf("\nPor favor insira uma ação válida\n");
					}
				}

				flag = 0;

				if( morte ){										//checar se algum inimigo morreu
                    printf("--------------------------------------------\n");
                    printf("\n%s morreu!\n", atual_enemy->actor.nome);
					RemoverBattle( battle_lista, &atual_enemy->actor );
					Remover( enemy, &atual_enemy->actor );
					enemy_battle_num--;
					morte = 0;
				}
			}else{
				if( atual_battle->actor.sts == 1){					//enemy turn
					while ( flag != 1 ){
						paux = Procurar( enemy, &atual_battle->actor );
						paux->actor.turndefend = 0;
						atual_hero = hero->inicio;

						srand (time(0));
						action = 1 + rand() % 3;

						switch( action ){
							case 1:
                                printf("--------------------------------------------\n");
                                attack = 1 + rand() % hero_battle_num;

								if( attack == 0 )
									break;

								for( int i = 1; i < attack; i++ ){
									atual_hero = atual_hero->next;
								}

								if( atual_hero->actor.turndefend ){	//checa se o alvo está defendendo
									sucess = AcertoFisico( atual_battle );
									if( sucess ){					//checa se o atacante acertou
										atual_hero->actor.hp = atual_hero->actor.hp - (atual_battle->actor.str+1)/2;
                                        printf("\n%s ataca, %s se defende e leva %d de dano!\n", atual_battle->actor.nome, atual_hero->actor.nome, (atual_battle->actor.str+1)/2);
									}else {
										printf("\n%s ataca mas erra!\n", atual_battle->actor.nome);
                                    }
								}else{
                                    sucess = AcertoFisico( atual_battle );
									if( sucess ){					//checa se o atacente acertou
										atual_hero->actor.hp = atual_hero->actor.hp - atual_battle->actor.str;
										printf("\n%s ataca e %s leva %d de dano!\n", atual_battle->actor.nome, atual_hero->actor.nome, atual_battle->actor.str);
									}else
										printf("\n%s ataca mas erra!\n", atual_battle->actor.nome);
								}

								if( atual_hero->actor.hp <= 0 )		//checa se o alvo está morto ou não
									morte++;

								flag++;
							break;

							case 2:
                                printf("--------------------------------------------\n");
								attack = 1 + rand() % hero_battle_num;

								if( attack == 0 )					//condição para voltar as ações
									break;

								for( int i = 1; i < attack; i++ ){
									atual_hero = atual_hero->next;
								}

								sucess = AcertoMagico( atual_battle );
								if( sucess ){						//checa se o atacante acertou
									atual_hero->actor.hp = atual_hero->actor.hp - atual_battle->actor.mag;
									printf("\n%s ataca com magia e %s leva %d de dano!\n", atual_battle->actor.nome, atual_hero->actor.nome, atual_battle->actor.mag);
								}else
									printf("\n%s ataca mas erra!\n", atual_battle->actor.nome);

								if( atual_hero->actor.hp <= 0 )		//checa se o alvo está morto ou não
									morte++;

								flag++;
							break;

							case 3:									//caso o inimigo escolha se defender
                                printf("--------------------------------------------\n");
                                printf("\n%s se defende!\n", atual_battle->actor.nome);
								paux = Procurar( enemy, &atual_battle->actor );
								paux->actor.turndefend = 1;

								flag++;
							break;
						}
					}

					flag = 0;

					if( morte ){									//checar se algum heroi morreu
						printf("\n%s morreu!\n", atual_hero->actor.nome);
						RemoverBattle( battle_lista, &atual_hero->actor );
						Remover( hero, &atual_hero->actor );
						hero_battle_num--;
						morte = 0;
					}
				}
			}
			if( enemy_battle_num <= 0 ){
				printf("\nParabens!\n Você derrotou todos os Inimigos!\n\n");
				break;
			}
			if( hero_battle_num <= 0 ){
				printf("\nDerrota!\n Todos os Hérois morreram\n\n");
				break;
			}
		}
		atual_battle = atual_battle->next;
	}
}

// ----------------------------------------------------------
/**
 * @brief Função que remove um elemento da lista ligada simples com sentinela
 *
 * Recebe endereço de lista licada circular com sentinela, endereço do elemento a ser removido;
 */
 // ----------------------------------------------------------
void RemoverBattle( LISTA_LIGADA *l, ACTOR *actor ){
		//Ponteiros
	_node *anterior = l->inicio;
	_node *atual = anterior->next;

	while ( 1 ){
		if( strcmp( atual->actor.nome, actor->nome) == 0 ){
			anterior->next = atual->next;
			free( atual );
			break;
		}
		anterior = anterior->next;
		atual = atual->next;
	}
}

// ----------------------------------------------------------
/**
 * @brief Função que libera a lista ligada circular com sentinela
 *
 * Recebe endereço de lista ligada circular com sentinela;
 */
 // ----------------------------------------------------------
void LiberarListaLigada( LISTA_LIGADA *l ){
		//Ponteiros
	_node *anterior = l->inicio;
	_node *atual = anterior->next;

	while( atual != anterior ){
		anterior->next = atual->next;
		free(atual);
		atual = anterior->next;
	}

	free(atual);
	return;

}

// ----------------------------------------------------------
/**
 * @brief Função que mostra o HP atual em relação do hp total de todos os elementos da lista de batalha
 *
 * Recebe endereço de lista ligada circular com sentinela, endereço de lista ligada simples com inimigos, endereço de lista ligada simples com heróis;
 */
 // ----------------------------------------------------------
void MostrarHP( LISTA_LIGADA *battle, LISTA_LIGADA *enemy, LISTA_LIGADA *hero ){
		//Ponteiros
	_node *atual_battle = battle->inicio;
	_node *atual_enemy_list = enemy->inicio;
	_node *atual_hero_list = hero->inicio;

	printf("Status:");
	while( atual_enemy_list != NULL ){
		while( 1 ){
			if( strcmp( atual_enemy_list->actor.nome, atual_battle->actor.nome) == 0 )
				break;

		atual_battle = atual_battle->next;
		}
		printf("\nInimigo\n");
		printf("%d/%d - %s\n", atual_enemy_list->actor.hp, atual_battle->actor.hp, atual_enemy_list->actor.nome);
		atual_enemy_list = atual_enemy_list->next;
		atual_battle = battle->inicio;
	}
    printf("\n--------------------------------------------\n");
	while( atual_hero_list != NULL ){
		while( 1 ){
			if( strcmp( atual_hero_list->actor.nome, atual_battle->actor.nome) == 0 )
				break;

		atual_battle = atual_battle->next;
		}
		printf("\nHerói\n");
		printf("%d/%d - %s\n", atual_hero_list->actor.hp, atual_battle->actor.hp, atual_hero_list->actor.nome);
		atual_hero_list = atual_hero_list->next;
		atual_battle = battle->inicio;
	}
}

// ----------------------------------------------------------
/**
 * @brief Diz se o atacande acertou o seu ataque fisico
 *
 * Recebe endereço do elemento;
 * Retorna 1 caso o alvo tenha acertado o ataque ou 0 caso o alvo tenha errado o ataque.
 */
 // ----------------------------------------------------------
int AcertoFisico( _node *atacante ){
		//Variáveis
	int acerto;
	int ran;

	acerto = 50 + (2.5*(atacante->actor.acc-1));

	srand (time(0));
	ran = 1 + rand() % 99;

	if( ran <= acerto )
		return 1;
	else
		return 0;
}

// ----------------------------------------------------------
/**
 * @brief Diz se o atacande acertou o seu ataque magico
 *
 * Recebe endereço do elemento;
 * Retorna o 1 caso o alvo tenha acertado o ataque ou 0 caso o alvo tenha errado o ataque.
 */
 // ----------------------------------------------------------
int AcertoMagico( _node *atacante ){
		//Variáveis
	int acerto;
	int ran;

	acerto = 35 + (2.15*(atacante->actor.acc-1));

	srand (time(0));
	ran = 1 + rand() % 99;

	if( ran <= acerto )
		return 1;
	else
		return 0;
}
