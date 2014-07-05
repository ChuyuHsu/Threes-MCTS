#ifndef _GAMEAGENT_GAME_H_
#define _GAMEAGENT_GAME_H_

#include "GameAgent.h"

class GameAgent::Game{
    private:
        Grid  m_grid;
        Grid  m_grid_backup;
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
        void  resetGrid();
        
        void  genNewTile();
        void  setNextTile();
        int   getNextTile();
        void  updateStats();
        void  setGameOver();
    public:
        Game();
        Game(Grid&);
        ~Game();
        void  reset();

        // inline
        char  getHint();
        void  getCurrentGrid(Grid& currGrid);
        bool  insertDirection(dir_e dir);
        bool  isGameOver(int& score);
        void  printGrid(int xPos, int yPos);
};


#endif
