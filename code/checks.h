#include <iostream>
#include "State.h"

#if !defined(CHECKS)
#define CHECKS

bool check_diags(State state, int x, int y){
    // token qui viens d'être mis. 
    int token = state.board[y*WIDTH+x]; 

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
                } else { acc = 0;}
                //test :
                //std::cout << state.board[(line)*WIDTH+col]<< " acc:" <<acc << " x:" << col << " y:"<< line <<"\n";
                
                col +=  right_or_left;
                line += up_or_down;
                }
            if (acc == 4) { // si diagonale complète :
                return true;
            }
        }
    }
    return false;
}


bool check_lines(State state, int x, int y){
    // token qui viens d'être mis. 
    int token = state.board[y*WIDTH+x];

    //Est-ce qu'il viens completer une line horizonale de 4 éléments ?
    for ( int right_or_left = -1 ; right_or_left <= 1 ; right_or_left = right_or_left+2){ // orientation de la line
        int acc = 0;
        int col = x;
        int line = y;
        for( int i = 0;  i < 4 && col < WIDTH && col >= 0 ; i++ ){
            if( state.board[(line)*WIDTH+col] == token){
                acc++;
            } else { acc = 0;}
            //test :
            //std::cout << state.board[(line)*WIDTH+col]<< " acc:" <<acc << " x:" << col << " y:"<< line <<"\n";
            col +=  right_or_left;
            }
        if (acc == 4) {
            return true;
        }
    }
    return false;
}

bool check_columns(State state, int x, int y){
    // token qui viens d'être mis. 
    int token = state.board[y*WIDTH+x];

    //Est-ce qu'il viens completer une line horizonale de 4 éléments ?
    for ( int up_or_down = -1 ; up_or_down <= 1 ; up_or_down = up_or_down+2){ //orientation de la colone
        int acc = 0;
        int col = x;
        int line = y;
        for( int i = 0;  i < 4 && line < HEIGHT && line >= 0; i++ ){
            if( state.board[(line)*WIDTH+col] == token){
                acc++;
            } else { acc = 0;}
            //test :
            //std::cout << state.board[(line)*WIDTH+col]<< " acc:" <<acc << " x:" << col << " y:"<< line <<"\n";

            line += up_or_down;
            }
        if (acc == 4) {
            return true;
        }
    }
    return false;
}

#endif // CHECKS
