#include "State.h"
#include <iostream>

State::State(){
    for(int c = 0; c < WIDTH; c++){
        this->board_ind[c] = 0;
        for(int l = 0; l < HEIGHT; l++){
            this->board[c*WIDTH+l] = 0;
        }
    }
}

State::State(player_e player){
    for(int c = 0; c < WIDTH; c++){
        this->board_ind[c] = 0;
        for(int l = 0; l < HEIGHT; l++){
            this->board[c*WIDTH+l] = 0;
        }
    }
    this->player = player;
}

State::State(State *old_state){
    for(int c = 0; c < WIDTH; c++){
        this->board_ind[c] = old_state->board_ind[c];
        for(int l = 0; l < HEIGHT; l++){
            this->board[c*WIDTH+l] = old_state->board[c*WIDTH+l];
        }
    }
    this->player = old_state->player;
}

void State::play(int column, bool &info){

    token_e token = (player == HUMAN) ? HU_CROSS : AI_ROUND;

    if(board_ind[column] < HEIGHT-1){
        board[HEIGHT* WIDTH - ((WIDTH - column )+(board_ind[column]) * WIDTH)] = token;
        board_ind[column]++;
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
