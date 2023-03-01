#include "Node.h"
#include <iostream> //TEMP

Node::Node(State* state){
    this->AI_turn = true;
    this->column = -1;
    this->n = 0;
    this->t = 0;
    this->state = state;
    this->parent = nullptr;
    this->children.reserve(WIDTH);
}

Node::Node(Node *parent, State *state){
    this->AI_turn = !parent->AI_turn;
    this->column = -1;
    this->n = 0;
    this->t = 0;
    this->state = state;
    this->children.reserve(WIDTH);
    this->parent = parent;
}

Node::~Node(){
    /*for(long unsigned int i = 0; i < this->children.size(); i++){
       children[i].~Node(); 
    }
    delete state;*/
}

void Node::develop_node(){
    std::cout << "develop_node"<< std::endl;
    //on arrive a un neud. on doit le developes
    if(this->n == 0 && this->children.size() == 0){ //leaf, not developed
        return this->rollout_node();
    }
    else if(this->n == 1 && this->children.size() == 0){ //leaf, developed once
        create_children();
        Node *child = choose_child();
        return child->develop_node();

    }else{//not a leaf
        Node *child = choose_child();
        return child->develop_node();
    }
}

void Node::backpropagate(end_e end){
    std::cout << "backpropagate" << std::endl;
    int score = compute_score(end);

    Node* current = this;
    while(current){
        current->t += score;
        current->n += 1;
        current = current->parent;
    }
}

State* Node::get_state(){
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
    std::cout << "UCB1" << (nod.t/nod.n) + std::sqrt(2*std::log((*nod.parent).n)/nod.n) <<std::endl;

    return (nod.t/nod.n) + std::sqrt(2*std::log((*nod.parent).n)/nod.n);
}

Node *Node::choose_child(){
    std::cout << "choose_children" <<this->children.size()<< std::endl;

    long unsigned int i = 0;
    float max = 0;
    Node *choosen_child = &this->children[0];

    do{

        Node *child = &this->children[i];

        if(child->get_n() == 0){
            choosen_child = child;
            break;
        }

        int ucb1 = UCB1(*child);

        if(ucb1 > max){
            max = ucb1;
            choosen_child = &this->children[i];
        }
        i++;
    }while(i < this->children.size());

    return choosen_child;
}

void Node::create_children(){
    std::cout << "create_children" << std::endl;

    int action = 0;
    bool info = true;

    while(action < WIDTH){
        
        State* next = new State(*this->state);
        next->play(action, info);

        if(info){
            Node child = Node(this, this->state);

            child.AI_turn = not(this->AI_turn);
            child.n = 0;
            child.t = 0;
            child.column = action;
            child.state = next;

            this->children.push_back(child);
        }

        //delete next;
        action ++;
    }
}

void Node::rollout_node(){
    std::cout << "Rollout_node" << std::endl;
    bool info;
    State simulation = State(*this->state);
    while(simulation.getEnd() == NONE){
        int next = std::rand() % 7;
        simulation.play(next, info);
    }
    this->backpropagate(simulation.getEnd());
}

int Node::compute_score(end_e end){
    std::cout << "Compute_score" << std::endl;
    
    if(end == NONE || end ==HU_VICTORY){
        return -1;

    }else if(end == EQUALITY){

        return 1;
    }else{

        return 5;
    }
}

int Node::choose_best(strat_e strategy){
    std::cout<<"score"<<this->children.size();
    Node best = this->children[0];
    if (strategy == MAX) {
        for (long unsigned int i = 0; i<this->children.size(); i++){
            std::cout<<this->children[i].get_t()<<"\n";
            if (this->children[i].get_t() >best.get_t()){
                best = this->children[i];
            }
        }
    }else if (strategy == ROBUST) {
        for (long unsigned int i = 0; i<this->children.size(); i++){
            std::cout<<this->children[i].get_n()<<"\n";
            if (this->children[i].get_n() >best.get_n()){
                best = this->children[i];
            }
        }
    }

    return best.get_column();
}