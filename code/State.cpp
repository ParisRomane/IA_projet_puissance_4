#include "checks.h"
#include <iostream>
#include "State.h"

State::State(){
    for(int c = 0; c < WIDTH; c++){
        this->board_ind[c] = 0;
        for(int l = 0; l < HEIGHT; l++){
            this->board[c*HEIGHT+l] = 0;
        }
    }

    last_played_x = 0;
    last_played_y = 0;
}

State::State(player_e player){
    for(int c = 0; c < WIDTH; c++){
        this->board_ind[c] = 0;
        for(int l = 0; l < HEIGHT; l++){
            this->board[c*HEIGHT+l] = 0;
        }
    }
    this->player = player;
    last_played_x = 0;
    last_played_y = 0;
}

State::State(State *old_state){
    for(int c = 0; c < WIDTH; c++){
        this->board_ind[c] = old_state->board_ind[c];
        for(int l = 0; l < HEIGHT; l++){
            this->board[c*HEIGHT+l] = old_state->board[c*HEIGHT+l];
        }
    }

    this->player = old_state->player;
    this->last_played_x = old_state->last_played_x;
    this->last_played_y = old_state->last_played_y;
}

bool State::is_full(){
    int acc = 0;

    for(int i = 0; i < WIDTH; i++){
        acc += this->board_ind[i];
    }

    return acc == HEIGHT * WIDTH;
}
void State::play(int column, bool &info)
{

    token_e token = (player == HUMAN) ? HU_CROSS : AI_ROUND;

    if(board_ind[column] < HEIGHT){
        board[board_ind[column]*WIDTH+column] = token;
        board_ind[column]++;
        player = (player == HUMAN) ? AI : HUMAN;
        info = true;

        this->last_played_x = column;
        this->last_played_y = board_ind[column]-1;
        //std::cout << getEnd() <<" \n";
    }else{

        info = false;
    }
}

std::vector<State> State::next_states(){

    std::vector<State> result;

    //For theses cases retrieve the infos is useless. All cases are playable.
    for(int i = 0; i < WIDTH; i++){
        if(board_ind[i] < HEIGHT){

            bool info;
            State next_state = State(this);
            next_state.play(i, info);

            result.push_back(next_state);
        }
    }
}

end_e State::getEnd(){
    if (check_diags(this, last_played_x, last_played_y)){
        return (this->player == HUMAN)? HU_VICTORY :AI_VICTORY;
    }
    if (check_lines(this, last_played_x, last_played_y)){
        return (this->player == HUMAN)? HU_VICTORY :AI_VICTORY;
    }
    if (check_columns(this, last_played_x, last_played_y)){
        return (this->player == HUMAN)? HU_VICTORY :AI_VICTORY;
    }
    if (is_full()){
        return EQUALITY;
    }
    
    return NONE;
}

player_e State::getPlayer(){

    return this->player;
}
