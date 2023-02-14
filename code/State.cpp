#include "checks.h"
#include <iostream>
#include "State.h"
#include  <cstdlib>
void PrintState(State state){
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

    if(column < WIDTH && column >= 0 && board_ind[column] < HEIGHT){
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

State State::next_states(){
    int max = 0 ;
    int choix = -1;
    bool info;
    State result = State(this);
    //For theses cases retrieve the infos is useless. All cases are playable.
    for(int i = 0; i < WIDTH; i++){
        if(board_ind[i] < HEIGHT){
            int gain = 0;
            for(int iter =0; iter<20; iter++){
                State next_state = State(this);
                while(next_state.getEnd()==NONE){
                    int next = std::rand() % 7;
                    next_state.play(next, info);
                }
                if(next_state.getEnd()==AI_VICTORY){
                    gain += 1;
                }
            }
            if(max<gain){
            max = gain;
            choix = i;
            }
        }
        
    }
    result.play(choix, info);
    return result;
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

std::tuple<int,int,int>  State::check_near_end(){
    State state = this;
    int x = this->last_played_x;
    int y = this->last_played_y;
    if(std::get<0>(check_pos_lines(state,x,y))!= -1)return check_pos_lines(state,x,y);
    if(std::get<0>(check_pos_columns(state,x,y))!= -1)return check_pos_columns(state,x,y);
    if(std::get<0>(check_pos_diags_1(state,x,y))!= -1)return check_pos_diags_1(state,x,y);
    if(std::get<0>(check_pos_diags_1(state,x,y))!= -1)return check_pos_diags_2(state,x,y);
    return std::make_tuple (-1,-1,-1);
}
