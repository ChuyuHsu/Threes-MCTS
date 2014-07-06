#ifndef _GAMEAGENT_H_
#define _GAMEAGENT_H_ 

#include "Threes.h"

class GameAgent
 {
 public:
    GameAgent(){};
    virtual ~GameAgent(){};
    virtual bool reset() = 0;
    virtual bool init() = 0;
    virtual dir_e getAction(Grid&, char) = 0; 

 protected: 
    class Game;

 private:
        /* data */
 };



#endif
