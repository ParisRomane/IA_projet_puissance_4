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
        
        std::vector<Node> childrens;
        Node *parent;
        State state;
        
        float UCB1(Node nod);

        Node choose_children();

        void create_childrens();

        Node rollout_node();

        int compute_score(bool isAI);

        Node simulate(Node nod);

    public:

        Node(State state);

        Node(Node *parent, State state);

        ~Node();

        Node develop_node();

        void backpropagate(bool isAI);

        State get_state();

        int get_n();

        int get_t();

        int get_column();

        bool is_AI_turn();
};

#endif // NODE
