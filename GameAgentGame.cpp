#include "GameAgent.h"
#include "GameAgentGame.h"


/*************************************************
                      Math
*************************************************/
// _pow3[i] = 3^(i+1) for i = 0 ~ (WHITE_TYPE_NUM - 1)
int _pow3[WHITE_TYPE_NUM] = 
{ 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441 };

// _log2()
// Description: base 2 log function for positive integers
// Arguments:
//     x  -  positive integer
// Return Val: logarithm of x with respect to base 2
int _log2(int x){
    assert(x > 0);
    int count = 0;
    while(x >>= 1)  count++;
    return count;
}


GameAgent::Game::Game(){
    init();
}

GameAgent::Game::Game(Grid& grid) {
    init();

    m_grid.copy(grid);
    m_grid_backup.copy(grid);
}

GameAgent::Game::~Game(){
}

void GameAgent::Game::reset(){
    updateStats();
    resetGrid();
    m_gameOver = FALSE;
    resetGrabBag();
    setNextTile();
        
}

void GameAgent::Game::init(){
    m_nRound = 0;
    m_moveCnt = 0;
    m_score = 0;
    m_maxScore = 0;
    m_scoreSum = 0;
    m_maxTile = 0;
    memset(m_passCnt, 0, sizeof(m_passCnt));
    m_gameOver = FALSE;
    resetGrabBag();
    setNextTile();

    m_startTime = cpuTime();
}

void GameAgent::Game::resetGrid(){
    m_grid.copy(m_grid_backup);
}

inline
int GameAgent::Game::getRand(){
    return rand();
}

inline
int GameAgent::Game::getNextTile(){
    return m_nextTile;
}

inline
char GameAgent::Game::getHint(){
    if(m_nextTile < BONUS_BASE)  return m_nextTile + '0';
    return '+';
}

inline
bool GameAgent::Game::isGameOver(int& score){
    if(m_gameOver){
        score = m_score;
        return TRUE;
    }
    else{
        score = 0;
        return FALSE;
    }
}

inline
int GameAgent::Game::getMaxScore(){
    return m_maxScore;
}

inline
void GameAgent::Game::resetGrabBag(){
    m_grabBag[0] = m_grabBag[1] = m_grabBag[2] = BAG_SIZE / BASIC_TYPE_NUM;
}

inline
bool GameAgent::Game::insertDirection(dir_e dir){
    if(!m_grid.shift(dir))  return FALSE;

    genNewTile();
    m_moveCnt++;
    setGameOver();
    return TRUE;
}

inline
void GameAgent::Game::getCurrentGrid(Grid& currGrid){
    currGrid.copy(m_grid);
}

inline
void GameAgent::Game::printGrid(int xPos, int yPos){
    m_grid.print(xPos, yPos);
}





void GameAgent::Game::genNewTile(){
    int nSlot = m_grid.getSlotNo();
    int randSlot = getRand() % nSlot;
    bool success = m_grid.setSlot(randSlot, getNextTile());
    assert(success);
    setNextTile();
}

void GameAgent::Game::setNextTile(){
    int maxTile = m_grid.getMaxTile();
    if(maxTile >= BONUS_THRESHOLD && getRand() % BONUS_RATIO == BONUS_RATIO - 1){
        int n = getRand() % (_log2(maxTile / BONUS_THRESHOLD) + 1);
        m_nextTile = (BONUS_BASE << n);
    }
    else{
        int tileType;
        int nTile = m_grabBag[0] + m_grabBag[1] + m_grabBag[2];
        assert(nTile > 0);
        int randTile = getRand() % nTile;
        if(randTile < m_grabBag[0]){
            m_grabBag[0]--;
            tileType = 1;
        }
        else if(randTile < m_grabBag[0] + m_grabBag[1]){
            m_grabBag[1]--;
            tileType = 2;
        }
        else{
            m_grabBag[2]--;
            tileType = 3;
        }
        if(nTile == 1)
            resetGrabBag();
        m_nextTile = tileType;
    }
}

void GameAgent::Game::updateStats(){
    m_nRound++;
    m_scoreSum += m_score;
    if(m_score > m_maxScore)
        m_maxScore = m_score;
    int maxTile = m_grid.getMaxTile();
    if(maxTile > m_maxTile)
        m_maxTile = maxTile;
 
    for(int i = 0;i < STAGE_NUM;i++){
        if(maxTile >= (FIRST_STAGE << i))
            m_passCnt[i]++;
    }
}

void GameAgent::Game::setGameOver(){
    if(m_grid.getEmptyBlkNo() > 0){
        m_gameOver = FALSE;
        return;
    }
    
    for(int i = 0;i < GRID_LENGTH;i++){
        for(int j = 0;j < GRID_LENGTH;j++){
            if( (i < GRID_LENGTH - 1) && m_grid.canMerge(m_grid(i,j),m_grid(i+1,j)) ){
                m_gameOver = FALSE;
                return;
            }
            if( (j < GRID_LENGTH - 1) && m_grid.canMerge(m_grid(i,j),m_grid(i,j+1)) ){
                m_gameOver = FALSE;
                return;
            }
        }
    }
    m_gameOver = TRUE;
    m_score = m_grid.getScore();
}



