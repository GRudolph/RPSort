#ifndef USEFUL_H
#include "usefulfunc.h"
#endif

#ifndef MY_USEFUL_LIBS
#include "usefullibs.h"
#endif

#include "state.h"
#include "Action.h"
#include "ActionList.h"
#include "qvalweb.h"
#include "qvaltree.h"
#include "edt.h"
#include "Agent.h"
#include "userdefined.h"

#define PROB 0.5
#define MAXVISITS 100000
#define MAXITERATIONS 1000

// The following are domain specific functions for generating the training
// states.  These essentially make a list of every possible combination.


int factorial(int n) 
{
	int result = 1;

	for (int i = 1; i <= n; i++) result *= i;

	return result;
}

bool permlexsuc(vector<int> &pi) 
{
	int n = pi.size();
	vector<int> temp(0);
	temp.reserve(n+1);
	temp.push_back(0);
	for (int i = 0; i < pi.size(); i++) 
		temp.push_back(pi[i]);

	int i = n-1;
	while (temp[i+1] < temp[i]) i--;
	if (i == 0) 
		return false;

	int j = n;
	while (temp[j] < temp[i]) j--;
	int t = temp[j];
	temp[j] = temp[i];
	temp[i] = t;

	vector<int> t2 = temp;

	for (int h = i+1; h <= n; h++) temp[h] = t2[n+i+1-h];

	for (int i = 0; i < pi.size(); i++) pi[i] = temp[i+1];

	return true;
}

vector<int> randlist(int size) {
	vector<int> result(0);
	result.reserve(size);

	for (int i = 1; i <= size; i++) result.push_back(i);

	for (int i = result.size()-1; i > 0; i--) {
		int loc = abs(rand()) % (result.size());
		int temp = result[i];
		result[i] = result[loc];
		result[loc] = temp;
	}

	return result;
}

//-----MAIN-----//

// An Agent object gets created, actions added to it, RP parameters are set 
// and the agent is run.

int main(int argc, char *argv[]) {
	
	int size = atoi(argv[1]);		// Size of the list.

	Agent* agent;
	agent = new Agent();
	
	// For now, we'll hard-code the RP parameters.  Later, command-line options
	// can be added to parse these parameters.
		
    agent->setDiscount(0.3);
    agent->setMaxIterations(1000);
    agent->setReportCount(1000);
    agent->setMaxVisits(100000);
    agent->setMaxIterationCount(1000000);
	
	// Create actions                     
	
	Action* noopAction = createAction(NOOPaction, NOOPcanAct, 
	                                  NOOPreward, "NOOP");
	Action* inciAction = createAction(INCIaction, INCIcanAct,
	                                  INCIreward, "i++;");
	Action* incjAction = createAction(INCJaction, INCJcanAct,
	                                  INCJreward, "j++;");
	Action* inckAction = createAction(INCKaction, INCKcanAct,
	                                  INCKreward, "k++;");
	Action* setizeroAction = createAction(SETIZEROaction, SETIZEROcanAct,
	                                      SETIZEROreward, "i=0;");
	Action* setjzeroAction = createAction(SETJZEROaction, SETJZEROcanAct,
	                                      SETJZEROreward, "j=0;");
	Action* setkzeroAction = createAction(SETKZEROaction, SETKZEROcanAct,
	                                      SETKZEROreward, "k=0;");
	Action* swapAction = createAction(SWAPaction, SWAPcanAct,
	                                  SWAPreward, "swap(i,j);");
	Action* terminateAction = createAction(TERMINATEaction, TERMINATEcanAct,
	                                       TERMINATEreward, "TERMINATE");

	// Add actions to the agent.

	agent->addAction(noopAction);
	agent->addAction(inciAction);
	agent->addAction(incjAction);
	agent->addAction(setizeroAction);
	agent->addAction(setjzeroAction);
	agent->addAction(swapAction);
	agent->addAction(terminateAction);
	agent->addAction(inckAction);
	agent->addAction(setkzeroAction);
	
	cout << "Actions Added!\n";
	
	// Good to here...Now, make some training states.
	
    vector< vector<int> > lists(0);
	lists.reserve(factorial(size));
	
	vector<int> list(0);
	list.reserve(size);
	for (int i = 1; i <= size; i++) list.push_back(i);
	
	do {
		lists.push_back(list);
	} while (permlexsuc(list));
	
	cout << "lists generated" << endl;	
	
	// Lists are made.  Now, create training states from these.
	
	state* tempState;
	dataStructure tempData;
	
	for (int i=0; i<lists.size(); i++)
	{
		tempState = new state();
		tempData = tempState->getData();
		tempData.list = lists[i];
		tempState->setData(tempData);
		
		agent->addTrainingState(tempState);
	}
	
	cout << "Training States Added!\n";
	
	for (int i=0; i<agent->trainingStates.size(); i++)
	{
	   cout << agent->trainingStates[i]->showData() << endl;
	}
	
	bool isTrained;
	
	// Run the agent.
	
	isTrained = agent->run();
	
	if(isTrained)
	{
		agent->printReport();
	}
	else
	{
		cout << "No Policy Found.\n";
	}
	
}

