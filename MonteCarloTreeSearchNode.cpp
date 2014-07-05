#include "MonteCarloTreeSearch.h"
#include "MonteCarloTreeSearchNode.h"

MonteCarloTreeSearch::Node::Node()
{
	wins = 0;
	visits = 0;
	move = -1;
	player = 0;
	parent = NULL;
	child = NULL;
	sibling = NULL;
	games = 0;
  
}

MonteCarloTreeSearch::Node::Node(Node* _parent, const HexGrid& _state, int _move, int _turn)
{
	parent = _parent;
	state = _state;
	
    move = _move;
	player = _turn;
	
	wins = 0;
	visits = 0;
	games = 0;
	child = NULL;
	sibling = NULL;
}

double MonteCarloTreeSearch::Node::getWinRate()
{
	if(visits != 0)
	{
		return (double) wins / (double) games;
	}
	else 
		return 0;
}

void MonteCarloTreeSearch::Node::backpropagation(int _wins, int _games)
{
	games += _games;
	wins += _wins;
	
	if(parent != NULL)
		parent->backpropagation(_wins, _games);
}

void MonteCarloTreeSearch::Node::createChildren()
{
	if(child != NULL) return;
	
	int width = this->state.getGridWidth();
	int height = this->state.getGridHeight();
	
	
	Node* last = NULL;
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			
			if(state.getCellState(i, j) == T_EMPTY)
			{
				int position = i*width+j;
				int _turn = (player == T_BLACK) ? T_WHITE : T_BLACK;
				
				HexGrid newState; 
			    newState = this->state;
				newState.setStone(position, player);

				
				Node* newNode = new Node(this, newState, position, _turn);
				if(last == NULL){
					this->child = newNode;
					// std::cout << newNode->move;
				}
				else
					last->sibling = newNode;
				last = newNode;
			}
		}
	}
}

Node* MonteCarloTreeSearch::Node::selection()
{
	visits++;
	Node* result = NULL;
	Node* next = this->child;
	std::cout << std::setw(3) << this->move;
	double best_uct = -100000;
	while(next != NULL)
	{
		double uctvalue = 0;
		if(next->visits > 0)
		{
			double winRate = next->getWinRate();
			if(player == T_BLACK) winRate = 1 - winRate;
			double uct = UCKT * sqrt( log(this->games) / next->games );
			uctvalue = winRate + uct; 
		}
		else
		{
			MyRand random;
			uctvalue = 50000 + 1000 * random.uniform();
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

int MonteCarloTreeSearch::Node::simulation(int _games)
{
	int wins = 0;
	for(int i = 0; i < _games; i++)
	{
		wins += (int) state.simulation(player);
	}
	return wins;
}

int MonteCarloTreeSearch::Node::finalDecision()
{
	Node* next = this->child;
	Node* result = this;
	
	double best_winRate = 0;
	while(next != NULL)
	{
		double winRate = next->getWinRate();
		if(winRate > best_winRate)
		{
			best_winRate = winRate;
			result = next;
		}
		next = next->sibling;
	}
	
	return result->move;
}




