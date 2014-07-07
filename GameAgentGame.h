#ifndef _GAMEAGENT_GAME_H_
#define _GAMEAGENT_GAME_H_

#include "GameAgent.h"

class GameAgent::Game{
    private:
        GameAgent::Game* backup;
        Grid  m_grid;
        bool  m_gameOver;
        int   m_nRound;
        int   m_score;
        int   m_maxScore;
        int   m_scoreSum;
        int   m_maxTile;
        int   m_passCnt[STAGE_NUM];
        int   m_moveCnt;
        int   m_grabBag[BASIC_TYPE_NUM];
        int   m_nextTile;
        double   m_startTime;
        double   m_endTime;

        // inline
        void  init();
        int   getRand();
        int   getMaxScore();         
        void  resetGrabBag();
       
        int   getNextTile();
        void  genNewTile();
        void  setNextTile();
        void  setNextTile(int);
        void  updateStats();
        void  setGameOver();
    public:
        Game();
        Game(Grid&, char&);
        Game(GameAgent::Game* parent);
        ~Game();
        void  reset();

        // inline
        char  getHint();
        void  getCurrentGrid(Grid& currGrid);
        bool  insertDirection(dir_e dir);
        bool  isGameOver(int& score);
        void  printGrid(int xPos, int yPos);
        void  copy(GameAgent::Game* p);
};


#endif
