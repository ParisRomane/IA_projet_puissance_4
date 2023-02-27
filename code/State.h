#include "structs.h"
#include <vector>

#if !defined(STATE)
#define STATE


class State{

    private:
        player_e player;
        int last_played_x;
        int last_played_y;

        bool is_full();

    public:

        int board_ind[WIDTH];
        int board[HEIGHT*WIDTH];

        void play(int column, bool &info);
        
        State next_states();

        end_e getEnd();

        player_e getPlayer();

        State();

        State(player_e player);

        State(const State &old_state);

        State* state_pointer(const State &state);

        int get_x(){return last_played_x;}

        int get_y(){return last_played_y;}

        std::tuple<int,int,int> check_near_end();

        void print_state();
};

#endif // STATE

void PrintState(State state);