#include <iostream>
#include "State.h"
#include <experimental/random>
#include <tuple>
#include <algorithm>
#include "Node.h"

int develop_tree(Node root, int time, strat_e strategy){
    std::cout << "develop_tree :";
    //on a ici le timer, et on fait tt les itérations
    int i = 0;
    Node node = Node(State());
    Node best = Node(State());
    

    while(i < time){
        root.develop_node();
        node = root;
        std::cout<<root.get_state().getEnd()<<" end for the cur_state..\n";
        node.backpropagate(node.is_AI_turn());

        if(strategy == MAX){
            best = best.get_n() < node.get_n() ? node : best;
        }else{
            best = best.get_t() < node.get_t() ? node : best;
        }
        i++;
    }
    std::cout << std::endl;

    // ensuite on retourne selon la stratégie, le meilleur noeud
    return best.get_column();
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

State ai_turn(State cur_state, std::vector<std::tuple<int,int,int>>* coup_gagnant){
    /*bool info;
    State next_state = State(cur_state);
    // Optimisation sur les coups gagnants.
    for (int i =0; i<coup_gagnant->size(); i++){
        int x = std::get<0>((*coup_gagnant)[i]);
        int y = std::get<1>((*coup_gagnant)[i]);
        std::cout<<"coup_gagnant"<<x<<" "<<y<<"\n";
        //on regarde si les coup sont faisable.
        if (next_state.board_ind[x] == y){ 
            next_state.play(x,info);
            coup_gagnant->erase(coup_gagnant->begin() + i);
    std::cout<<"coup_1 "<<coup_gagnant->size();
            return next_state;
        }
        
    }
    std::cout<<"coup_2 "<<coup_gagnant->size();
    return next_state.next_states();*/

    bool info;

    std::cout<<cur_state.get_x()<<"\n";

    Node root = Node(cur_state);
    State next_state = State(cur_state);

    std::cout<< root.get_state().getEnd() << " end for the cur_state..\n";

    next_state.play(develop_tree(root, 1, ROBUST), info);

    std::cout << root.get_state().getEnd() << " end for the cur_state..\n";
    return next_state;
}

int main(int argc, char* argv[]){

    std::vector<std::tuple<int,int,int>> coup_gagnant;
    std::tuple<int,int,int> coup;
    State state = State(HUMAN);
    bool info;

    end_e end = NONE;
    int i = 1;

    state.print_state();
    while(end == NONE){
        i = (i + 1) % 2;
        state = (i == 0) ? player_turn(state) : ai_turn(state,&coup_gagnant);

        // on regarde si le coup réalise/annule un coup gagnant : 
        std::find(coup_gagnant.begin(), coup_gagnant.end(), coup) != coup_gagnant.end();
        // regarde si le coup fait est un final ou une ligne de 3 avec un vide
        // oui mais si un coup annule un coup ?
        coup = state.check_near_end();
        if (std::get<0>(coup)!=-1) coup_gagnant.push_back(coup);
        end = state.getEnd();
        state.print_state();
    }
    std::cout << end << std::endl;
    
    return EXIT_SUCCESS;
}
