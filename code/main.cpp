#include "State.h"
#include <iostream>

bool info;

void print_state(State state){
    std::cout << "---------------" << std::endl;
    for(int i = 0; i < WIDTH; i++){
        std::cout << "|";
        for(int j = 0; j < HEIGHT; j++){

            if(state.board[i*j] == HU_CROSS){
                std::cout << "X|";
            }else if(state.board[i*j] == AI_ROUND){
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

    return EXIT_SUCCESS;
}
