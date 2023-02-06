#include <iostream>
#include "State.h"

bool info;

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

    std::cout << ((state.getPlayer() == HUMAN) ? "Your turn." : "Turn of the computer.") << std::endl
        << "Debug info : " << info << std::endl << std::endl;
}

int main(int argc, char* argv[]){


    State state = State(HUMAN);
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
    print_state(state);
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
    print_state(state);
    
    return EXIT_SUCCESS;
}
