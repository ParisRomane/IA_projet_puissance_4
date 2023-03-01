#include "structs.h"
#include <vector>
#include <tuple>

#if !defined(STATE)
#define STATE


class State{

    private:
        player_e player;
        int last_played_x;
        int last_played_y;

        bool is_full();

    public:
        std::vector<std::tuple<int,int,int>> coup_gagnantAI;
        std::vector<std::tuple<int,int,int>> coup_gagnantHU;

        int board_ind[WIDTH];
        int board[HEIGHT*WIDTH];

        void play(int column, bool &info);
        
        void next_s();

        end_e getEnd();

        player_e getPlayer();

        State();

        State(player_e player);

        State(const State &old_state);

        int get_x(){return last_played_x;}

        int get_y(){return last_played_y;}

        void check_near_end();

        void print_state();

        int possible_coup_gagnant();
};

#endif // STATE

void PrintState(State state);