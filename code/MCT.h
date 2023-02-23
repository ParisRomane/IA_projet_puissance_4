#include "structs.h"
#include "State.h"
#include <math.h>

struct node {
   int t=0;   
   int n=0;
   bool AI_turn;
   int column;
   struct node *children[WIDTH]; 
   struct node *parent = nullptr; 
   State state;
}; // si n = 0 on choisi -> infini

struct MC_tree {
   struct node *root;
};

float UCB1(node nod);

node choose_children(node parent);

void create_children(node nod);

MC_tree create_tree(State state);

int develop_tree(MC_tree tree, int time, strat_e strategy);

node rollout_node(node nod);

//FONCTION POUR RÉUTILISER L'ARBRE, et ne pas le redev de 0 à chaque fois.
node develop_node(node nod);

void backpropagate(node *nod, bool isAI);

int compute_score(node nod, bool isAI);

node simulate(node nod);
