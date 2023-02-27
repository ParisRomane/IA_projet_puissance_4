#include "State.h"
#include <assert.h>
#include <math.h>

#if !defined(NODE)

#define NODE

class Node{
    private:
        int t=0;   
        int n=0;
        bool AI_turn;
        int column;
        
        std::vector<Node> children;
        Node *parent;
        State* state;
        
        float UCB1(Node nod);

        Node choose_child();

        void rollout_node();

        int compute_score();


    public:

        Node(State* state);

        Node(Node *parent, State* state);

        ~Node();

        void develop_node();

        void backpropagate();

        State* get_state();

        int get_n();

        int get_t();

        int get_column();

        int choose_best(strat_e strategy);

        bool is_AI_turn();

        void create_children();
};

#endif // NODE
