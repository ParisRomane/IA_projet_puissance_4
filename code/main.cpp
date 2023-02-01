#include "State.h"
#include <iostream>

bool info;

void print_state(State state){
    std::cout << "---------------" << std::endl;
    for(int col = 0; col < WIDTH; col++){
        std::cout << "|";
        for(int ligne = 0; ligne < HEIGHT; ligne++){
            if(state.board[ligne+col*HEIGHT] == HU_CROSS){
                std::cout << "X " <<ligne+col*HEIGHT <<"|";
                
            }else if(state.board[ligne+col*HEIGHT] == AI_ROUND){
                std::cout << "O"<<ligne+col*HEIGHT <<"|";
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
