#include "structs.h"

#define HEIGHT 7
#define WIDTH 6

class State{

    private:
        player_e player;
    public:

        int board_ind[WIDTH];
        int board[HEIGHT*WIDTH];

        void play(int column, bool &info);

        State next_state();

        end_e getEnd();

        player_e getPlayer();

        State();

        State(player_e player);

        State(State* old_state);
};