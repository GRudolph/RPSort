#ifndef __AGENT_H__
#define __AGENT_H__

#include "qvaltree.h"
#include "edt.h"

#define PROB 0.5

static const int NOOP = -1;
//static const int INCI = 0;	
//static const int INCJ = 1;
//static const int SETIZERO = 2;	
//static const int SETJZERO = 3;
static const int SWAP = 4;
//static const int TERMINATE = 5;
//static const int INCK = 6;
//static const int SETKZERO = 7;

// Agent 
// 
// The Agent class is the controller for the RP process.  It allows the user
// to add actions, run the agent and print a policy.

class Agent
{
   private:
      double discount;
      int maxIterations;
      int maxIterationCount;
      int reportCount;
      int maxVisits;
      qvaltree *tree;
       
   public:
      ActionList* actionList; 
      vector<state*> trainingStates;
   
      Agent();
      ~Agent();
      
      void addAction(Action *);
      void addTrainingState(state*);
      bool transition(int, state &);
      int learn(state &, qvaltree *);
      int treesort(state &, qvaltree *, bool);
      void setDiscount(double);
      void setMaxIterations(int);
      void setMaxIterationCount(int);
      void setReportCount(int);
      void setMaxVisits(int);
      bool run();
      void printReport();
};

#endif
