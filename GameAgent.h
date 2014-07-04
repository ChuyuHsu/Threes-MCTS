#ifndef _GAMEAGENT_H_
#define _GAMEAGENT_H_ 

#include "Threes.h"

class GameAgent
 {
 public:
    GameAgent();
    ~GameAgent();
    virtual bool reset();
    virtual bool init();
    virtual dir_e getAction(const Grid&, const char&); 
 private:
    class Game;
    /* data */
 };



#endif
