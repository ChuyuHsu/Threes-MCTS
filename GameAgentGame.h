#ifndef _GAMEAGENT_GAME_H_
#define _GAMEAGENT_GAME_H_

#include "GameAgent.h"

class GameAgent::Game{
    private:
        static int   m_objCount;
        static bool  m_objInit;

        static Grid  m_grid;
        static bool  m_gameOver;
        static int   m_nRound;
        static int   m_score;
        static int   m_maxScore;
        static int   m_scoreSum;
        static int   m_maxTile;
        static int   m_passCnt[STAGE_NUM];
        static int   m_moveCnt;
        static int   m_grabBag[BASIC_TYPE_NUM];
        static int   m_nextTile;
        static double   m_startTime;
        static double   m_endTime;

        // inline
        void  init();
        int   getRand();
        int   getMaxScore();         
        void  resetGrabBag();
        void  resetGrid();
        
        void  genInitTile();
        void  genNewTile();
        void  setNextTile();
        int   getNextTile();
        void  updateStats();
        void  setGameOver();
    public:
        Game();
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
