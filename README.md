Threes-MCTS
===========

Threes! AI with [Monte-Carlo Tree Search]. 
This project is for [Taiwan 2048 Bot] competition.
In this project, the threes! agent uses the monte-carlo tree search with UCT for the first trial.
In the meantime, the other member is implementing a expeciminimax algorithm which has outperformed this MCTS algorithm.

Under the time constriant, the number of simulation is way too small. 
  * Accelarate the simulation process
  * Improve the original UCT algorithm



File Description: 
----
Only covers the .h header files, but include coresponsing .cpp files 

  - Threes.h are provided by the competition organizer
  - myrand.h, statistics.h and mt19937ar.h are from [Dr. Yu]
  - GameAgent.h: interface of search algorithm
  - GameAgentGame.h: class Game for simulation
  - MonteCarloTreeSearch.h: the general framework 
  - MonteCarloTreeSearchNode.h: how MCTS actually works, UCT values are calculted here
  


[Monte-Carlo Tree Search]: http://en.wikipedia.org/wiki/Monte-Carlo_tree_search
[Taiwan 2048 Bot]: http://2048-botcontest.twbbs.org
[Dr. Yu]: http://teilab.ee.ntu.edu.tw
