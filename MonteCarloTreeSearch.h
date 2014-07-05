#ifndef _MCTS_H_
#define _MCTS_H_ 

#include "GameAgent.h"

#define TRIAL_NUM 100

class MonteCarloTreeSearch : public GameAgent
{
public:
    MonteCarloTreeSearch();
    ~MonteCarloTreeSearch();
    
    bool reset();
    bool init();
    dir_e getAction(Grid&, char&); 

protected:
    class Node;

private:
    /* data */
};

#endif


