#include <iostream>
#include "State.h"

#if !defined(CHECKS)
#define CHECKS

end_e switch_stmt(int statement, int & acc_hu, int & acc_ai){

    switch (statement){
        case HU_CROSS:
            acc_hu ++;
            acc_ai = 0;
        break;
        
        case AI_ROUND:
            acc_hu = 0;
            acc_ai ++;
        break;
    
        default:    //VOID
            return NONE;
        break;
    }

    if(acc_hu == 4){
        std::cout << "HU " << acc_hu << " " << ((acc_hu == 4) ? "True" : "False") << std::endl;
        return HU_VICTORY;
    }

    if(acc_ai == 4){
        std::cout << "AI" << acc_ai << std::endl;
        return AI_VICTORY;
    }
}

end_e check_upward_diag(State state, int x, int y){
    int acc_hu = 0;
    int acc_ai = 0;

    for(int i = x; i >= x; i++){
        for(int j = HEIGHT; j >= y; j--){

            end_e res = switch_stmt(state.board[j*WIDTH + i], acc_hu, acc_ai);

            if(res == HU_VICTORY && AI_VICTORY){
                return res;
            }
        }
    }
    
    return NONE;
}

end_e check_downward_diag(State state, int x, int y){

    int acc_hu = 0;
    int acc_ai = 0;

    for(int i = x; i >= x; i++){
        for(int j = y; j < HEIGHT; j++){

            end_e res = switch_stmt(state.board[j*WIDTH + i], acc_hu, acc_ai);
            
            if(res == HU_VICTORY || res == AI_VICTORY){
                return res;
            }
        }
    }

    return NONE;
}

end_e check_line(State state, int y){

    int acc_hu = 0;
    int acc_ai = 0;

    for(int i = 0; i < WIDTH; i++){

        end_e res = switch_stmt(state.board[y*WIDTH + i], acc_hu, acc_ai);
            
        if(res == HU_VICTORY && AI_VICTORY){
            return res;
        }
    }

    return NONE;
}

end_e check_column(State state, int x){

    int acc_hu = 0;
    int acc_ai = 0;

    for(int i = 0; i < HEIGHT; i++){

        end_e res = switch_stmt(state.board[i*WIDTH + x], acc_hu, acc_ai);
            
        if(res == HU_VICTORY && AI_VICTORY){
            return res;
        }
    }

    return NONE;
}

#endif // CHECKS
