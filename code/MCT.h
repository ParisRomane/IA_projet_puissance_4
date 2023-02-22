#include "structs.h"
#include <math.h>
struct node {
   int t=0;   
   int n=0;
   bool IA_turn;
   int column;
   struct node *children[WIDTH]; 
   struct node *parent = nullptr; 
}; // si n = 0 on choisi -> infini

struct MC_tree {
   struct node *root;
};

float UCB1(node nod){ // suppose nod.n != 0
    return (nod.t/nod.n) + std::sqrt(2*std::log((*nod.parent).n)/nod.n);
}

node choose_children(node parent){
    int i = 0;
    float max = 0;
    node choosen_child;
    do{
        node child = *(parent.children[i]);
        if(child.n == 0){
            choosen_child = child;
            break;
        }
        if (UCB1(choosen_child)>max){
            max = UCB1(choosen_child);
            choosen_child = *(parent.children[i]);
        }
        
    }while(i<6);
    return choosen_child;
}

void create_children(node nod){
    // il faut checker si les coups sont possibles aussi
    for (int i=0; i< WIDTH; i++){
        node child;
        child.column = i;
        child.IA_turn = not(nod.IA_turn);
        nod.children[i] = &child;
    }
}

MC_tree create_tree(){
    node root;
    root.column = -1;
    root.IA_turn = 1;
    create_children(root);
    MC_tree tree;
    tree.root = &root;
    return tree;
}

void develop_tree(MC_tree tree, int time, strat_e strategy){
    //on a ici le timer, et on fait tt les itérations
    while(1 != 0){
        create_tree();
    }
    // ensuite on retourne selon la stratégie, le meilleur noeud
}

void rollout_node(node nod){
    // déjà plus ou moins fait.
    while(1 != 0){
        create_tree();
    }
}

void develop_node(node nod){
    //on arrive a un neud. on doit le develloper
    if(nod.n == 0){ //leaf, not develloped
        rollout_node(nod);
    }
    else if(nod.n == 1){ //leaf, develloped once
        create_children(nod);
        node child = choose_children(nod);
        develop_node(child);
    }else{//not a leaf
        node child = choose_children(nod);
        develop_node(child);
    }
}
//FONCTION POUR RÉUTILISER L'ARBRE, et ne pas le redev de 0 à chaque fois.