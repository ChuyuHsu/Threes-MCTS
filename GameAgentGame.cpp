#include "GameAgent.h"
#include "GameAgentGame.h"

int _log2(int);

GameAgent::Game::Game(){
    init();
}

GameAgent::Game::Game(GameAgent::Game* parent) {
    init();
    this->copy(parent);
    this->backup = NULL;
    //std::cout << "p: " << parent << "b:" << backup << std::endl;
}

GameAgent::Game::Game(Grid& grid, char& hint){
    init();
    m_grid.copy(grid);
    if(hint != 0)
        if(hint != '+')
            setNextTile(hint - '0');
}

GameAgent::Game::~Game(){
    //std::cout << "this " << this <<  " b:" << backup << std::endl;
    delete backup;
}

void GameAgent::Game::reset(){
    if(backup)
        this->copy(backup); 
}

void GameAgent::Game::copy(GameAgent::Game* parent){
    this->m_grid.copy(parent->m_grid);
    this->m_gameOver = parent->m_gameOver;
    this->m_nRound = parent->m_nRound;
    this->m_moveCnt = parent->m_moveCnt;
    this->m_score = parent->m_score;
    this->m_scoreSum = parent->m_scoreSum;
    this->m_maxScore = parent->m_maxScore;
    this->m_maxTile = parent->m_maxTile;
    this->setNextTile();
    memcpy(this->m_passCnt, parent->m_passCnt, STAGE_NUM);
    memcpy(this->m_grabBag, parent->m_grabBag, BASIC_TYPE_NUM);

    this->backup = parent;
}

void GameAgent::Game::init(){
    backup = NULL;
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

int GameAgent::Game::getRand(){
    return rand();
}

int GameAgent::Game::getNextTile(){
    return m_nextTile;
}

char GameAgent::Game::getHint(){
    if(m_nextTile < BONUS_BASE)  return m_nextTile + '0';
    return '+';
}

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

int GameAgent::Game::getMaxScore(){
    return m_maxScore;
}

void GameAgent::Game::resetGrabBag(){
    m_grabBag[0] = m_grabBag[1] = m_grabBag[2] = BAG_SIZE / BASIC_TYPE_NUM;
}

bool GameAgent::Game::insertDirection(dir_e dir){
    //m_grid.print(200,50); 
    //std::cout << std::endl << dir  << std::endl;
    if(!m_grid.shift(dir))  return FALSE;

    genNewTile();
    m_moveCnt++;
    setGameOver();
    return TRUE;
}

void GameAgent::Game::getCurrentGrid(Grid& currGrid){
    currGrid.copy(m_grid);
}

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
        if(nTile == 0) {
            resetGrabBag();
            nTile = m_grabBag[0] + m_grabBag[1] + m_grabBag[2];
        }
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

void GameAgent::Game::setNextTile(int tileType){
    m_nextTile = tileType;
    m_grabBag[tileType]--;
    if(m_grabBag[0] + m_grabBag[1] + m_grabBag[2] == 0)
        resetGrabBag();
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


