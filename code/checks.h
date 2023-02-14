#include <iostream>
#include "State.h"
#include <tuple>

#if !defined(CHECKS)
#define CHECKS

bool check_diags(State state, int x, int y){
    // token qui viens d'être mis. 
    int token = state.board[y*WIDTH+x]; 
    std::vector<int> bornes ;
    //Est-ce qu'il viens completer une diagonale de 4 éléments ?
    for ( int right_or_left = -1 ; right_or_left <= 1 ; right_or_left = right_or_left+2){  //diagonale vers la droite ou gauche ?
        for ( int up_or_down = -1 ; up_or_down <= 1 ; up_or_down = up_or_down+2){ //diagonale vers le haut ou bas ?
            // initialisation :
            int acc = 0;
            int col = x;
            int line = y;
            //construction de la diagonale :
            for( int i = 0;  i < 4 && col < WIDTH && col >= 0 && line < HEIGHT && line >= 0; i++ ){
                if( state.board[(line)*WIDTH+col] == token){
                    acc++;
                } else {break;}
                bornes.push_back(acc) ;
                col +=  right_or_left;
                line += up_or_down;
            }
        }
    }
    if ( bornes[0] + bornes[2] == 5 && bornes[1] + bornes[3] == 5) { // si diagonale complète :
        return true;
    }
    return false;
}


bool check_lines(State state, int x, int y){
    // token qui viens d'être mis. 
    int token = state.board[y*WIDTH+x];
    int acc = 0;
    //Est-ce qu'il viens completer une line horizonale de 4 éléments ?
    for ( int right_or_left = -1 ; right_or_left <= 1 ; right_or_left = right_or_left+2){ // orientation de la line
        int col = x;
        int line = y;
        for( int i = 0;  i < 4 && col < WIDTH && col >= 0 ; i++ ){
            if( state.board[(line)*WIDTH+col] == token){
                acc++;
            } else {break;}
            col +=  right_or_left;
        }
    }
    if ( acc == 5) { // si diagonale complète :
        return true;
    }
    return false;
}

bool check_columns(State state, int x, int y){
    // token qui viens d'être mis. 
    int token = state.board[y*WIDTH+x];
    int acc = 0;
    //Est-ce qu'il viens completer une line horizonale de 4 éléments ?
    for ( int up_or_down = -1 ; up_or_down <= 1 ; up_or_down = up_or_down+2){ //orientation de la colone
        int col = x;
        int line = y;
        for( int i = 0;  i < 4 && line < HEIGHT && line >= 0; i++ ){
            if( state.board[(line)*WIDTH+col] == token){
                acc++;
            } else {break;}
            //test :
            //std::cout << state.board[(line)*WIDTH+col]<< " acc:" <<acc << " x:" << col << " y:"<< line <<"\n";

            line += up_or_down;
        }
    }
    if ( acc == 5) { // si diagonale complète :
        return true;
    }
    return false;
}

std::tuple<int,int> check_end_diags(State state, int x, int y){
    // token qui viens d'être mis. 
    int token = state.board[y*WIDTH+x]; 
    std::vector<int> bornes ;
    std::tuple<int,int> void_index (-1,-1);
    //Est-ce qu'il viens completer une diagonale de 4 éléments ?
    for ( int right_or_left = -1 ; right_or_left <= 1 ; right_or_left = right_or_left+2){  //diagonale vers la droite ou gauche ?
        for ( int up_or_down = -1 ; up_or_down <= 1 ; up_or_down = up_or_down+2){ //diagonale vers le haut ou bas ?
            // initialisation :
            int acc = 0;
            int col = x;
            int line = y;
            //construction de la diagonale :
            for( int i = 0;  i < 4 && col < WIDTH && col >= 0 && line < HEIGHT && line >= 0; i++ ){
                if( state.board[(line)*WIDTH+col] == token){
                    acc++;
                }else if( state.board[(line)*WIDTH+col] == VOID){
                    if (void_index != std::make_tuple (-1,-1)){
                        break;
                    }
                    void_index = std::make_tuple (col, line);
                }  else {break;}
                bornes.push_back(acc) ;
                col +=  right_or_left;
                line += up_or_down;
            }
        }
    }
    if ( bornes[0] + bornes[2] == 4 && bornes[1] + bornes[3] == 4) { // si diagonale complète :
        return void_index;
    }
    return std::make_tuple (-1,-1);
}


int check_end_lines(State state, int x, int y){
    // token qui viens d'être mis. 
    int token = state.board[y*WIDTH+x];
    int acc = 0;
    int already_void = -1;
    //Est-ce qu'il viens completer une line horizonale de 4 éléments ?
    for ( int right_or_left = -1 ; right_or_left <= 1 ; right_or_left = right_or_left+2){ // orientation de la line
        int col = x;
        int line = y;
        for( int i = 0;  i < 4 && col < WIDTH && col >= 0 ; i++ ){
            if( state.board[(line)*WIDTH+col] == token){
                acc++;
            }else if( state.board[(line)*WIDTH+col] == VOID){
                if (already_void != -1){
                    break;
                }
                already_void= col;
            }  else {break;}
            col +=  right_or_left;
        }
    }
    if ( acc == 4) { // si diagonale complète :
        return already_void;
    }
    return -1;
}

int check_end_columns(State state, int x, int y){
    // token qui viens d'être mis. 
    int token = state.board[y*WIDTH+x];
    int acc = 0;
    int already_void = -1;
    //Est-ce qu'il viens completer une line horizonale de 4 éléments ?
    for ( int up_or_down = -1 ; up_or_down <= 1 ; up_or_down = up_or_down+2){ //orientation de la colone
        int col = x;
        int line = y;
        for( int i = 0;  i < 4 && line < HEIGHT && line >= 0; i++ ){
            if( state.board[(line)*WIDTH+col] == token){
                acc++;
            }else if( state.board[(line)*WIDTH+col] == VOID){
                if (already_void != -1){
                    break;
                }
                already_void= col;
            }  else {break;}
            //test :
            //std::cout << state.board[(line)*WIDTH+col]<< " acc:" <<acc << " x:" << col << " y:"<< line <<"\n";

            line += up_or_down;
        }
    }
    if ( acc == 4) { // si diagonale complète :
        return already_void;
    }
    return -1;
}

#endif // CHECKS
