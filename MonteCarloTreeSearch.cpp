#include "MonteCarloTreeSearch.h"
#include "MonteCarloTreeSearchNode.h"
#include "GameAgentGame.h"

MonteCarloTreeSearch::MonteCarloTreeSearch() {
    
}

MonteCarloTreeSearch::~MonteCarloTreeSearch() {
    
}

bool MonteCarloTreeSearch::init() {
    return true;
}

bool MonteCarloTreeSearch::reset() {
    return true;
}

dir_e MonteCarloTreeSearch::getAction(Grid& grid, char hint) {
    int i;
    //std::cout << "MCTS initialized" << std::endl;
    GameAgent::Game* game = new GameAgent::Game(grid, hint);
    //game->printGrid(50,30);
    Node* root = new Node(NULL, *game, -1);
	
	//root->state.dumpGrid();
	//root.search();
    clock_t begin_time = clock();

	while(( float( clock () - begin_time ) /  CLOCKS_PER_SEC) < (TIMELIMIT - 0.0001))
	{
        //std::cout << "select" << std::endl;
		//1. select: select a position not added to the tree.
		Node* selectedNode = root->selection();

        //std::cout << "expansion" << std::endl;
		//2. expansion: 
		selectedNode->expansion();
       
        //std::cout << "simulation" << std::endl;
		//3. simulation
		selectedNode->simulation(SIMULATION_TIMES);
        
        //std::cout << "backpropagation" << std::endl;
		//4. backpropagation
		selectedNode->backpropagation();
		// cout << "Now game Simulated " << root->games << "! \n";	
	}
	
	dir_e output = (dir_e)root->finalDecision();
	std::cout << "\nTotal game Simulated " << root->getTimes() << "! \n";	
    delete root;
	return output;
}


