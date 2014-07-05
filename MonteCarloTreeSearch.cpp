#include "MonteCarloTreeSearch.h"

MonteCarloTreeSearch::MonteCarloTreeSearch() {
    
}

MonteCarloTreeSearch::~MonteCarloTreeSearch() {
    
}

bool MonteCarloTreeSearch::init() {
    
}

bool MonteCarloTreeSearch::reset() {
    
}

dir_e MonteCarloTreeSearch::getAction(Grid& grid, char& hint) {
	Node* root = new Node(NULL, grid, -1);
	//root->createChildren();
	//root->state.dumpGrid();
	//root.search();
	
	while(( float( clock () - begin_time ) /  CLOCKS_PER_SEC) < (timeLimit - 0.02))
	{
		//1. select: select a position not added to the tree.
		Node* selectedNode = root->selection();

		//2. expansion: 
		selectedNode->expansion();
        
		//3. simulation
		int result = selectedNode->simulation(SIMULATION_TIMES);
        
		//4. backpropagation
		selectedNode->backpropagation(result, SIMULATION_TIMES);
		// cout << "Now game Simulated " << root->games << "! \n";	
	}
	
	int output = root->finalDecision();
	cout << "Total game Simulated " << root->games << "! \n";	
	return output;
}


