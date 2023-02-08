#include <iostream>
#include "State.h"
#include <experimental/random>

void print_state(State state){
    std::cout << "---------------" << std::endl;
    for(int line = 0; line < HEIGHT; line++){
        std::cout << "|";
        for(int col = 0; col < WIDTH; col++){
            if(state.board[HEIGHT* WIDTH - ((WIDTH - col )+ line * WIDTH)] == HU_CROSS){
                std::cout << "X|";
            }else if(state.board[HEIGHT* WIDTH - ((WIDTH - col )+ line * WIDTH)]  == AI_ROUND){
                std::cout << "O|";
            }else{
                std::cout << " |";
            }
        }
        std::cout << std::endl << "---------------" << std::endl;
    }

    std::cout << ((state.getPlayer() == HUMAN) ? "Your turn." : "Turn of the computer.") << std::endl << std::endl;
}

State player_turn(State cur_state){

    int column;
    bool info = false;
    State next_state = State(cur_state);

    do{

        std::cout << "Which column ? ";
        std::cin >> column;
        std::cout << std::endl;

        next_state.play(column, info);

        if(!info){
            std::cout << "That move is impossible." << std::endl << std::endl;
        }

    }while (!info);

    return next_state;
}

State ai_turn(State cur_state){

    auto next_states = cur_state.next_states();
    /*int i = std::experimental::randint(0, (int)next_states.size() - 1);

    std::cout << i << std::endl;*/

    //return next_states[i];
}

int main(int argc, char* argv[]){


    State state = State(HUMAN);
    bool info;
    //TEST COLONES
    /*
    print_state(state);
    state.play(1, info);
    print_state(state);
    state.play(2, info);
    print_state(state);
    state.play(2, info);
    print_state(state);
    state.play(3, info);
    print_state(state);
    state.play(3, info);
    print_state(state);
    state.play(4, info);
    print_state(state);
    state.play(3, info);
    print_state(state);
    state.play(4, info);
    print_state(state);
    state.play(4, info);
    print_state(state);
    state.play(5, info);
    print_state(state);
    state.play(4, info);
    print_state(state);*/

    //TEST LIGNES :
    /*print_state(state);
    state.play(1, info);
    print_state(state);
    state.play(1, info);
    print_state(state);
    state.play(2, info);
    print_state(state);
    state.play(2, info);
    print_state(state);
    state.play(3, info);
    print_state(state);
    state.play(3, info);
    print_state(state);
    state.play(4, info);
    print_state(state);*/

    //TEST COLONES :
    /*print_state(state);
    state.play(1, info);
    print_state(state);
    state.play(2, info);
    print_state(state);
    state.play(1, info);
    print_state(state);
    state.play(2, info);
    print_state(state);
    state.play(1, info);
    print_state(state);
    state.play(2, info);
    print_state(state);
    state.play(1, info);
    print_state(state);*/

    end_e end = NONE;
    int i = 1;

    print_state(state);
    while(end == NONE){
        i = (i + 1) % 2;
        state = (i == 0) ? player_turn(state) : ai_turn(state);

        end = state.getEnd();
        print_state(state);
    }
    std::cout << end << std::endl;
    
    return EXIT_SUCCESS;
}
