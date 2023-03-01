#include "checks.h"
#include <iostream>
#include "State.h"
#include  <cstdlib>

State::State(){
    for(int c = 0; c < WIDTH; c++){
        this->board_ind[c] = 0;
        for(int l = 0; l < HEIGHT; l++){
            this->board[c*HEIGHT+l] = 0;
        }
    }
    this->coup_gagnantAI = {};
    this->coup_gagnantHU = {};
    player = AI;
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
    this->coup_gagnantAI = {};
    this->coup_gagnantHU = {};
    this->player = player;
    last_played_x = -1;
    last_played_y = -1;
}

State::State(const State &old_state){
    for(int c = 0; c < WIDTH; c++){
        this->board_ind[c] = old_state.board_ind[c];
        for(int l = 0; l < HEIGHT; l++){
            this->board[c*HEIGHT+l] = old_state.board[c*HEIGHT+l];
        }
    }
    this->coup_gagnantAI = std::vector(old_state.coup_gagnantAI);
    this->coup_gagnantHU = std::vector(old_state.coup_gagnantHU);
    this->player = old_state.player;
    this->last_played_x = old_state.last_played_x;
    this->last_played_y = old_state.last_played_y;
}

bool State::is_full(){
    int acc = 0;

    for(int i = 0; i < WIDTH; i++){
        acc += this->board_ind[i];
    }

    return acc == HEIGHT * WIDTH;
}

void State::play(int column, bool &info){

    token_e token = (player == HUMAN) ? HU_CROSS : AI_ROUND;

    if(column < WIDTH && column >= 0 && board_ind[column] < HEIGHT){
        board[board_ind[column]*WIDTH+column] = token;
        board_ind[column]++;
        player = (player == HUMAN) ? AI : HUMAN;
        info = true;

        this->last_played_x = column;
        this->last_played_y = board_ind[column]-1;
        this->check_near_end();
    }else{

        info = false;
    }
}

int State::possible_coup_gagnant(){
    std::cout<<"SIZE "<<this->coup_gagnantAI.size()<<" "<<this->coup_gagnantHU.size()<<"\n";
    for (int i =0; i<this->coup_gagnantAI.size(); i++){

        int x = std::get<0>((this->coup_gagnantAI)[i]);
        int y = std::get<1>((this->coup_gagnantAI)[i]);

        //on regarde si les coup sont faisable.
        if (this->board_ind[x] == y){ 
            this->coup_gagnantAI.erase(this->coup_gagnantAI.begin() + i);
            std::cout<<"yes ! \n";
            return x;
        }
    }    
    for (int i =0; i<this->coup_gagnantHU.size(); i++){

        int x = std::get<0>((this->coup_gagnantHU)[i]);
        int y = std::get<1>((this->coup_gagnantHU)[i]);

        //on regarde si les coup sont faisable.
        if (this->board_ind[x] == y){ 
            this->coup_gagnantHU.erase(this->coup_gagnantHU.begin() + i);
            std::cout<<"yes ! \n";
            return x;
        }
    }
    return -1;
}

void State::next_state(){
    bool info;
    int coup = this->possible_coup_gagnant();
    if (coup >= 0){
        this->play(coup, info);
    }else{
        int next = std::rand() % 7;
        this->play(next, info);}
}

end_e State::getEnd(){

    if (check_diags(*this, last_played_x, last_played_y)){
        return (this->player == HUMAN)? HU_VICTORY :AI_VICTORY;
    }

    if (check_lines(*this, last_played_x, last_played_y)){
        return (this->player == HUMAN)? HU_VICTORY :AI_VICTORY;
    }

    if (check_columns(*this, last_played_x, last_played_y)){
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

void  State::check_near_end(){
    State state = State(*this);
    int x = this->last_played_x;
    int y = this->last_played_y;
    if(std::get<0>(check_pos_lines(state,x,y))!= -1){
        if(std::get<2>(check_pos_lines(state,x,y))== 2){
            this->coup_gagnantAI.push_back(check_pos_lines(state,x,y));
        }
        if(std::get<2>(check_pos_lines(state,x,y))== 1){
            this->coup_gagnantHU.push_back(check_pos_lines(state,x,y));
            }
    }
    if(std::get<0>(check_pos_columns(state,x,y))!= -1){
        if(std::get<2>(check_pos_columns(state,x,y))== 2){
            this->coup_gagnantAI.push_back(check_pos_columns(state,x,y));
        }
        if(std::get<2>(check_pos_columns(state,x,y))== 1){
            this->coup_gagnantHU.push_back(check_pos_columns(state,x,y));
            }
    }
    if(std::get<0>(check_pos_diags_1(state,x,y))!= -1){
        if(std::get<2>(check_pos_diags_1(state,x,y))== 2){
            this->coup_gagnantAI.push_back(check_pos_diags_1(state,x,y));
        }
        if(std::get<2>(check_pos_diags_1(state,x,y))== 1){
            this->coup_gagnantHU.push_back(check_pos_diags_1(state,x,y));
            }
    }
    if(std::get<0>(check_pos_diags_2(state,x,y))!= -1){
        if(std::get<2>(check_pos_diags_2(state,x,y))== 2){
            this->coup_gagnantAI.push_back(check_pos_diags_2(state,x,y));
        }
        if(std::get<2>(check_pos_diags_2(state,x,y))== 1){
            this->coup_gagnantHU.push_back(check_pos_diags_2(state,x,y));
            }
    }
}

void State::print_state(){
    std::cout << "---------------" << std::endl;
    for(int line = 0; line < HEIGHT; line++){
        std::cout << "|";
        for(int col = 0; col < WIDTH; col++){
            if(board[HEIGHT* WIDTH - ((WIDTH - col )+ line * WIDTH)] == HU_CROSS){
                std::cout << "X|";
            }else if(board[HEIGHT* WIDTH - ((WIDTH - col )+ line * WIDTH)]  == AI_ROUND){
                std::cout << "O|";
            }else{
                std::cout << " |";
            }
        }
        std::cout << std::endl << "---------------" << std::endl;
    }

    std::cout << ((player == HUMAN) ? "Your turn." : "Turn of the computer.") << std::endl << std::endl;
}
