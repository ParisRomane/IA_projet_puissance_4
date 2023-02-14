#include <iostream>
#include "State.h"
#include <experimental/random>
#include <tuple>

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
    //ce check est a faire 2 fois !!! a chaque coup -> début et fin de cette fonction
    bool info;
    if (std::get<0>(cur_state.check_near_end())!=-1){
        State next_state = State(cur_state);
        std::cout<<std::get<0>(cur_state.check_near_end());
        next_state.play(std::get<0>(cur_state.check_near_end()), info);
        return next_state;
    }
    cur_state.play(0,info);
    return cur_state;
}

int main(int argc, char* argv[]){


    State state = State(HUMAN);
    bool info;

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
