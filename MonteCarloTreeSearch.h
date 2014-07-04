#ifndef _MCTS_H_
#define _MCTS_H_ 

#include "GameAgent.h"
class MonteCarloTreeSearch : public GameAgent
{
public:
    MonteCarloTreeSearch();
    ~MonteCarloTreeSearch();
    
    bool reset();
    bool init();
    dir_e getAction(const Grid&, const char&); 
private:
    /* data */
};

#endif


