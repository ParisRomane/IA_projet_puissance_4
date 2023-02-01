#include "State.h"
#include <iostream>

State::State(){
    for(int i = 0; i < WIDTH; i++){
        this->board_ind[i] = 0;
        for(int j = 0; j < HEIGHT; j++){
            this->board[i*j] = 0;
        }
    }
}

State::State(player_e player){
    for(int i = 0; i < WIDTH; i++){
        this->board_ind[i] = 0;
        for(int j = 0; j < HEIGHT; j++){
            this->board[i*j] = 0;
        }
    }

    this->player = player;
}

State::State(State *old_state){

    for(int i = 0; i < WIDTH; i++){
        this->board_ind[i] = old_state->board_ind[i];
        for(int j = 0; j < HEIGHT; j++){
            this->board[i*j] = old_state->board[i*j];
        }
    }

    this->player = old_state->player;
}

void State::play(int column, bool &info){

    token_e token = (player == HUMAN) ? HU_CROSS : AI_ROUND;

    if(board_ind[column] < HEIGHT-1){
        std::cout<< board[0] <<" "<< HEIGHT* WIDTH - ((WIDTH - column +1 )+(board_ind[column]) * HEIGHT)<< "\n";
        board[HEIGHT* WIDTH - ((WIDTH - column +1 )+(board_ind[column]) * HEIGHT)] = token;
        std::cout<< board[0];
        board_ind[column]++;
        std::cout<< board[0];
        player = (player == HUMAN) ? AI : HUMAN;
        info = true;

    }else{

        info = false;
    }
}

State State::next_state(){

    //TODO
}

end_e State::getEnd(){

    //TODO
}

player_e State::getPlayer()
{
    return this->player;
}
