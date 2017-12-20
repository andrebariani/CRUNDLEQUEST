#ifndef _LISTA_
#define _LISTA_

#define MAX 201

// ----------------------------------------------------------
/**
 * @brief Registro de um heroi ou inimigo.
 */
// ----------------------------------------------------------

typedef struct {
    int hp;
	int str; //!< Dano Físico.
	int mag;  //!< Dano Mágico.
	int def;   //!< Defesa.
	int acc; //!< Precisão de um ataque.
	int spd; //!< Velocidade, define quem ataca primeiro.
	int sts;  //!< Indicador de herói ou inimigo.
    int turndefend;  //!< Indicador de aumento de defesa por um turno de combate.
    char nome[MAX];  //!< Nome do personagem
} ACTOR;
// ----------------------------------------------------------
/**
 * @brief Nó de uma lista ligada.
 */
// ----------------------------------------------------------

typedef struct _node{
    struct _node *next;  //!< Ponteiro para próximo nó na lista.
    ACTOR actor; //!< Registro de um personagem pertencente ao nó.
}_node;

// ----------------------------------------------------------
/**
 * @brief Lista Ligada
 */
// ----------------------------------------------------------

typedef struct {
    _node *inicio; //!< Ponteiro para inicio da lista ligada.
} LISTA_LIGADA;

int Inserir( LISTA_LIGADA *l, ACTOR *actor );
_node *Procurar( LISTA_LIGADA *l, ACTOR *actor );
int Remover( LISTA_LIGADA *l, ACTOR *actor );
void LiberarLista( LISTA_LIGADA *primeiro );

#endif
