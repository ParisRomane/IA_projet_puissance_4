#include "structs.h"
#include <vector>

#if !defined(STATE)
#define STATE

#define HEIGHT 6
#define WIDTH 7

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

        State(State* old_state);

        int get_x(){return last_played_x;}

        int get_y(){return last_played_y;}

        void check_near_end(std::vector<std::tuple<int,int,int>>* coups);

};

#endif // STATE

void PrintState(State state);