#include <iostream>
#include "State.h"
#include <experimental/random>
#include <tuple>
#include <algorithm>
#include "Node.h"
#include <ctime>
#include <vector>

int develop_tree(Node root, int time, strat_e strategy){
    std::cout << "develop_tree :";

    clock_t begin = clock();
    clock_t end = clock();

    State empty_state = State();
    Node best = Node(&empty_state);
    
    root.create_children();
    while((end - begin) < time){    //Time in millis
        root.develop_node();
        end = clock();
    }
    std::cout << root.get_t()<< std::endl;

    // ensuite on retourne selon la stratégie, le meilleur noeud
    return root.choose_best(MAX);
}

State player_turn(State cur_state){

    std::string column;
    bool info = false;
    State next_state = State(cur_state);

    do{

        std::cout << "Which column ? ";
        std::cin >> column;
        std::cout << std::endl;
        std::cout << stoi(column);
        if(!stoi(column)){
            std::cout << "please enter int." << std::endl << std::endl;
        }

        next_state.play(stoi(column), info);
        if(!info){
            std::cout << "That move is impossible." << std::endl << std::endl;
        }

    }while (!info);

    return next_state;
}

State ai_turn(State cur_state){

    bool info;

    Node root = Node(&cur_state);
    State next_state = State(cur_state);
    int coup = next_state.possible_coup_gagnant();
    if(coup != -1){
        next_state.play(coup,info);
        return next_state;
    }

    next_state.play(develop_tree(root, 1000, ROBUST), info);

    return next_state;
}

int main(int argc, char* argv[]){

    State state = State(HUMAN);

    end_e end = NONE;
    int i = 1;

    state.print_state();
    while(end == NONE){
        i = (i + 1) % 2;
        state = (i == 0) ? player_turn(state) : ai_turn(state);
        end = state.getEnd();
        state.print_state();
    }
    std::cout << end << std::endl;
    
    if(end == AI_VICTORY)std::cout<<"LA MACHINE A GAGNÉE";
    else if(end == HU_VICTORY)std::cout<<"VOUS AVEZ GAGNÉ";
    else std::cout<<" ÉGALITÉE";

    return EXIT_SUCCESS;
}
