#include "MCT.h"
#include <iostream> // TEMP

float UCB1(node nod){ // suppose nod.n != 0

    return (nod.t/nod.n) + std::sqrt(2*std::log((*nod.parent).n)/nod.n);
}

node choose_children(node* parent){
    int i = 0;
    float max = 0;
    node* choosen_child = empty_node(parent->state);

    do{

        node* child = parent->children[i];

        if(child->n == 0){
            choosen_child = child;
            break;
        }

        int ucb1 = UCB1(*choosen_child);

        if (ucb1>max){
            max = ucb1;
            choosen_child = parent->children[i];
        }
        
    }while(i < parent->children.size());

    return *choosen_child;
}

void create_children(node* nod){
    // il faut checker si les coups sont possibles aussi
    /*for (int i = 0; i < WIDTH; i++){
        node child;

        child.column = i;
        child.AI_turn = not(nod.AI_turn);
        nod.children[i] = &child;
    }*/

    int action = 0;
    bool info = true;

    while(action < WIDTH){
        State next = State(nod->state);
        next.play(action, info);

        if(info){
            node* child = empty_node(nod->state);

            child->AI_turn = not(nod->AI_turn);
            child->n = 0;
            child->t = 0;
            child->column = action;
            child->parent = nod;
            child->state = next;

            nod->children.push_back(child);
        }

        action ++;
    }
}

MC_tree create_tree(State state){

    node *root = empty_node(state);
    MC_tree tree;

    tree.root = root;

    return tree;
}

int develop_tree(MC_tree tree, int time, strat_e strategy){
    std::cout << "develop_tree :";
    //on a ici le timer, et on fait tt les itérations
    int i = 0;
    node* nod = empty_node(State());
    node* best = empty_node(State());
    

    while(i < time){
        develop_node(tree.root);
        nod = tree.root;
        std::cout<<(*tree.root).state.getEnd()<<" end for the cur_state..\n";
        backpropagate(nod, nod->AI_turn);

        if(strategy == MAX){
            best = best->n < nod->n ? nod : best;
        }else{
            best = best->t < nod->t ? nod : best;
        }
        i++;
    }
    std::cout << std::endl;

    // ensuite on retourne selon la stratégie, le meilleur noeud
    return best->column;
}

node rollout_node(node* nod){
    std::cout << "Rollout_node : ";
    std::cout<<nod->state.getEnd()<<" end for the cur_state..\n";

    while(true){
        if(nod->state.getEnd() != NONE){ //Terminal state
            std::cout << "terminal state case " << nod->state.getEnd() <<std::endl;
            return *nod;
        }else{
            std::cout << "non-terminal state case";
            nod = simulate(nod);
        }
    }
}

// FONCTION POUR RÉUTILISER L'ARBRE, et ne pas le redev de 0 à chaque fois.
node develop_node(node* nod){
    std::cout << "Develop_node : ";

    //on arrive a un neud. on doit le developes
    if(nod->n == 0){ //leaf, not developed
        std::cout << "leaf not developed " << nod->n << std::endl;
        return rollout_node(nod);
    }

    else if(nod->n == 1){ //leaf, developed once
        std::cout << "leaf developed once" << std::endl;
        create_children(nod);
        node child = choose_children(nod);
        return develop_node(&child);

    }else{//not a leaf
        std::cout << "not a leaf" << std::endl;
        node child = choose_children(nod);
        return develop_node(&child);
    }
}

void backpropagate(node *nod, bool isAI){
    std::cout << "Backpropagate : ";
    node* current = nod;

    while(current){
        std::cout<< current->t << " "<<current->n <<current->state.get_x()<<" \n";
        current->t += compute_score(*current, isAI);
        current->n += 1;
        current = current->parent;
    }
    std::cout << std::endl;
}

int compute_score(node nod, bool isAI){
    std::cout << "Compute_score : ";
    end_e end = nod.state.getEnd();
    
    if(end == NONE){
        std::cout << "none" << std::endl;
        return 0;
    }else if(end == EQUALITY){
            std::cout << "equality" << std::endl;
            return 1;
    }else{
        if(end == HU_VICTORY){
            std::cout << "human victory" << std::endl;
            return isAI ? 0 : 5;
        }else{
            std::cout << "AI victory" << std::endl;
            return isAI ? 5 : 0;
        }
    }
}

node* simulate(node *nod){
    std::cout << "Simulate : ";
    bool status = false;
    node* res = empty_node(State());

    res->AI_turn = !nod->AI_turn;
    res->n = nod->n;
    res->t = nod->t;
    res->parent = nod;

    while(!status){
        res->state = State(nod->state);
        int action = rand() % WIDTH;
        res->state.play(action, status);
        res->column = action;
    }

    std::cout << std::endl;
    return res;
}

node *empty_node(State state){
    node* nod;

    nod->n = 0;
    nod->t = 0;
    nod->column = -1;
    nod->AI_turn = 1;
    nod->state = State(state);

    return nod;
}
