#include "Node.h"

Node::Node(State state){
    this->AI_turn = true;
    this->column = -1;
    this->n = 0;
    this->t = 0;
    this->state = state;
    this->parent = nullptr;
    this->childrens.reserve(WIDTH);
}

Node::Node(Node *parent, State state){
    this->AI_turn = !parent->AI_turn;
    this->column = -1;
    this->n = 0;
    this->t = 0;
    this->state = state;
    this->childrens.reserve(WIDTH);
    this->parent = parent;
}

Node::~Node(){
    for(int i = 0; i < this->childrens.size(); i++){
       childrens[i].~Node(); 
    }
}

Node Node::develop_node(){
    //on arrive a un neud. on doit le developes
    if(this->n == 0){ //leaf, not developed
        return rollout_node();
    }

    else if(this->n == 1){ //leaf, developed once
        create_childrens();
        Node child = choose_children();
        return child.develop_node();

    }else{//not a leaf
        Node child = choose_children();
        return child.develop_node();
    }
}

void Node::backpropagate(bool isAI){
    
    Node* current = this;

    while(current){
        current->t += current->compute_score(isAI);
        current->n += 1;
        current = current->parent;
    }
}

State Node::get_state(){
    return state;
}

int Node::get_n(){
    return n;
}

int Node::get_t(){
    return t;
}

int Node::get_column(){
    return column;
}

bool Node::is_AI_turn(){
    return AI_turn;
}

float Node::UCB1(Node nod){
    assert(nod.n != 0);
    return (nod.t/nod.n) + std::sqrt(2*std::log((*nod.parent).n)/nod.n);
}

Node Node::choose_children(){
    int i = 0;
    float max = 0;
    Node choosen_child = Node(parent, parent->state);

    do{

        Node child = parent->childrens[i];

        if(child.n == 0){
            choosen_child = child;
            break;
        }

        int ucb1 = UCB1(choosen_child);

        if(ucb1 > max){
            max = ucb1;
            choosen_child = parent->childrens[i];
        }
        
    }while(i < parent->childrens.size());

    return choosen_child;
}

void Node::create_childrens(){
    int action = 0;
    bool info = true;

    while(action < WIDTH){
        State next = State(this->state);
        next.play(action, info);

        if(info){
            Node child = Node(this, this->state);

            child.AI_turn = not(this->AI_turn);
            child.n = 0;
            child.t = 0;
            child.column = action;
            child.state = next;

            this->childrens.push_back(child);
        }

        action ++;
    }
}

Node Node::rollout_node(){
    while(true){

        Node node = Node(this, this->state);

        if(this->state.getEnd() != NONE){ //Terminal state
            return node;
        }else{
            node = simulate(node);
        }
    }
}

int Node::compute_score(bool isAI){

    end_e end = this->state.getEnd();
    
    if(end == NONE){
        return 0;

    }else if(end == EQUALITY){

        return 1;
    }else{

        if(end == HU_VICTORY){

            return isAI ? 0 : 5;
        }else{

            return isAI ? 5 : 0;
        }
    }
}

Node Node::simulate(Node nod){
    
    bool status = false;
    Node res = Node(this, State());

    res.n = this->n;
    res.t = this->t;

    while(!status){
        res.state = State(this->state);
        int action = rand() % WIDTH;
        res.state.play(action, status);
        res.column = action;
    }

    return res;
}
