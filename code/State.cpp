#include "State.h"


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

        board[(board_ind[column]+1) * HEIGHT] = token;
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
