#include <float.h>
#include "MonteCarloTreeSearch.h"
#include "MonteCarloTreeSearchNode.h"


MonteCarloTreeSearch::Node::Node()
{
	visits = 0;
	move = -1;
	parent = NULL;
	child = NULL;
	sibling = NULL;
	games = 0;
    score = 0;
  
}

MonteCarloTreeSearch::Node::Node(Node* _parent, Game& _state, int _move)
{
	parent = _parent;
	state.copy(&_state);
    //state.printGrid(150,30);
    move = _move;

	score = 0;
	visits = 0;
	games = 0;
	child = NULL;
	sibling = NULL;
}

MonteCarloTreeSearch::Node::~Node(){
    if(this->sibling)
        delete this->sibling;
    if(this->child)
        delete this->child;

}


void MonteCarloTreeSearch::Node::backpropagation()
{
	if(parent != NULL)
		parent->backpropagation(this->score, this->games);
}

void MonteCarloTreeSearch::Node::backpropagation(int _score, int _games)
{
    score += _score;
    games += _games;

	if(parent != NULL)
		parent->backpropagation(_score, _games);
}

void MonteCarloTreeSearch::Node::createChildren()
{
	if(child != NULL) return;
	
	Node* last = this->child;

    for (int i = 0; i < 4; i++) {
        GameAgent::Game*  childGame = new GameAgent::Game(&state);
        if(!childGame->insertDirection( (dir_e)i) )
        {
            delete childGame;
            continue;
        }
        
        Node* newNode = new Node(this, *childGame, i);
        
        if(last == NULL){
           this->child = newNode;
            // std::cout << newNode->move;
        }
        else
            last->sibling = newNode;
        last = newNode;
    }

}

MonteCarloTreeSearch::Node* MonteCarloTreeSearch::Node::selection()
{
	visits++;
    //std::cout << std::endl << "MOVE:" << this->move << std::endl;
    MonteCarloTreeSearch::Node* result = NULL;
    MonteCarloTreeSearch::Node* next = this->child;
	//std::cout << std::setw(3) << this->move;
	double best_uct = -100000;
	while(next != NULL)
	{
		double uctvalue = 0;
		if(next->visits > 0)
		{
			uctvalue = this->getUCTValue(next); 
		}
		else
		{
			MyRand random;
			uctvalue = DBL_MAX;
		}
        
		if(uctvalue > best_uct)
		{
			best_uct = uctvalue;
			result = next;
		}
		next = next->sibling;
	}
	
	//visit == 0, this node is not in the tree yet.
	if(!result) return this;
	// else if(result->visits == 0) return result;
	else return result->selection();
}

void MonteCarloTreeSearch::Node::expansion() 
{ 
	visits++; 
	createChildren();
}

double MonteCarloTreeSearch::Node::simulation(int _games)
{
	//double score = 0;
    int r=0;
	for(int i = 0; i < _games; i++)
	{
        this->state.reset();
        r = this->randomPlay();
        score += r;
        sta.record(r);
        //std::cout << "Simulation Score:" << score << std::endl;
	}
    games += _games;
	return (double) score / _games;
}

int MonteCarloTreeSearch::Node::randomPlay(){
    int i,score = 0;
    bool dir[4] = {1,1,1,1}; 
    bool b = false;
    //state.printGrid(70,30);
    while (!state.isGameOver(score)) {
        dir_e move = (dir_e)random.uniformInt(0, 3);
        
        b = state.insertDirection(move);
       
       // if(b)
       //     std::cin.ignore();
        

    }
    //std::cout << "SCORE:"<<score << std::endl;
    return score;
}

int MonteCarloTreeSearch::Node::finalDecision()
{
	Node* next = this->child;
	Node* result = this;
    //std::cout << "MOVE:" << this->move << std::endl;
	double bestScore = -DBL_MAX;
	while(next != NULL)
	{
	    //std::cout << "MOVE:" << next->move 
        //            << ", Score: " << next->getScoreMean() 
        //            << ", visits:" << next->visits
        //            << ", score:" << next->score
        //            << ", games:" << next->games
        //            << std::endl;
       
		double score = next->getScoreMean();
		if(score > bestScore)
		{
			bestScore = score;
			result = next;
		}
		next = next->sibling;
	}
	
	return result->move;
}

#define C 5
#define D 1
double MonteCarloTreeSearch::Node::getUCTValue(Node* c){

    double mean = score / games;
    double exploration = 2 * C * sqrt(log(this->games)/c->games);
    //double deviation = sqrt( (c->getVariance() + D) / c->games );

    return mean + exploration;
}

double MonteCarloTreeSearch::Node::getScoreMean(){
    if(visits > 0)
        return (double)score / games;
    else 
        return 0.0;
}

int MonteCarloTreeSearch::Node::getTimes(){
    return (int)this->games;
}
