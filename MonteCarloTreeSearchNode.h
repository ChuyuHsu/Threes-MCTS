#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "Threes.h"
#include "MonteCarloTreeSearch.h"

#ifndef __NODE_H
	#define __NODE_H
	typedef unsigned int uint; 
    
class MonteCarloTreeSearch::Node
{
public:
   Node();
   Node(Node* parent, Grid& state, int move, int _turn);

   uint wins;
   uint games;
   uint visits;
   int move;
   int player; // either T_BLACK or T_WHITE
   Grid state;
   Node* parent;
   Node* child;
   Node* sibling;

   double getWinRate();
   void backpropagation(int _wins, int _games);
   void createChildren();
   Node* selection();
   void expansion();
   int simulation(int _games);
   int finalDecision();
};

#endif