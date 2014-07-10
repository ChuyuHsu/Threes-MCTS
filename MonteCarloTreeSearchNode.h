#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "Threes.h"
#include "MonteCarloTreeSearch.h"
#include "GameAgentGame.h"
#include "myrand.h"
#include "statistics.h"

#ifndef __NODE_H
	#define __NODE_H
	typedef unsigned int uint; 
    
class MonteCarloTreeSearch::Node
{
public:
   Node();
   Node(Node* _parent, GameAgent::Game& _state, int _move);
   virtual ~Node();
   
   void backpropagation();
   Node* selection();
   double simulation(int _games);
   int finalDecision();
   void expansion();
   int getTimes();
protected:   
   virtual double getScoreMean();
   virtual double getUCTValue(Node*);
   virtual void createChildren();

   Statistics sta;
   uint games;
   uint visits;
   uint score;
   int move;
   GameAgent::Game state;
   Node* parent;
   Node* child;
   Node* sibling;

private:
   void backpropagation(int _score, int _games);
   int randomPlay();
   MyRand random;
};

#endif
