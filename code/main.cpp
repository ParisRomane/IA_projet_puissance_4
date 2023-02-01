#include "State.h"
#include <iostream>

bool info;

void print_state(State state){
    std::cout << "---------------" << std::endl;
    for(int ligne = 0; ligne < HEIGHT; ligne++){
        std::cout << "|";
        for(int col = 0; col < WIDTH; col++){
            if(state.board[ligne*WIDTH+col] == HU_CROSS){
                std::cout << "X|";
            }else if(state.board[ligne*WIDTH+col] == AI_ROUND){
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

    print_state(state);
    state.play(1, info);
    print_state(state);
    state.play(1, info);
    print_state(state);
    state.play(6, info);
    print_state(state);
    state.play(6, info);
    print_state(state);
    
    return EXIT_SUCCESS;
}
