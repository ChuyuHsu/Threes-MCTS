#ifndef _MCTS_H_
#define _MCTS_H_ 

#include <ctime>
#include "GameAgent.h"

#define SIMULATION_TIMES 100
#define TIMELIMIT 0.02
class MonteCarloTreeSearch : public GameAgent
{
public:
    MonteCarloTreeSearch();
    ~MonteCarloTreeSearch();
    
    bool reset();
    bool init();
    dir_e getAction(Grid&, char); 

protected:
    class Node;

private:
    /* data */
};

#endif


