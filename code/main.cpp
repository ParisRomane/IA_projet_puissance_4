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

    std::cout<<cur_state.get_x()<<"\n";

    Node root = Node(&cur_state);
    State next_state = State(cur_state);

    std::cout<< root.get_state()->getEnd() << " end for the cur_state..\n";

    next_state.play(develop_tree(root, 100, ROBUST), info);

    std::cout << root.get_state()->getEnd() << " end for the cur_state..\n";
    return next_state;
}

int main(int argc, char* argv[]){

    State state = State(HUMAN);
    bool info;

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
    
    return EXIT_SUCCESS;
}
