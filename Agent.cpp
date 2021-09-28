#include "Agent.h"

// Constructor -- create a new ActionList to store the actions passed to this.

Agent::Agent()
{
   actionList = new ActionList();
   discount = 0.0;
}

// Destructur -- delete the ActionList

Agent::~Agent()
{
	delete actionList;
}

// addAction -- add an action to the ActionList.

void Agent::addAction(Action *action)
{
    actionList->addAction(action);
}

// addTrainingState -- add a new state to the list to train this Agent.

void Agent::addTrainingState(state* trainingState)
{
    trainingStates.push_back(trainingState);
}

// transition - perform an action on the state and determine the new state by
// recalculating the comparisons.

bool Agent::transition(int actionID, state &s) 
{
	bool results = actionList->getAction(actionID+1)->act(s);

	s.setLastActionID(actionID);

	s.buildcomps();

	return results;
}

// learn - update Q values for the state by performing actions.

int Agent::learn(state &curstate, qvaltree *tree) 
{
	dataStructure stateData = curstate.getData();
	int reward;

	qvalweb *qvw = tree->getqvw(curstate);

	int itercount = 0;

    bool terminate = false;

	while (!terminate && itercount < maxIterations) 
	{
		itercount++;

		int act = qvw->bestact;

		if (act == NOOP || qvw->qval < 0 || abs(drand48()) > PROB)
		{ 

			act = actionList->getRandomAction(curstate);
		}

		terminate = transition(act, curstate);

		qvalweb *nqvw = tree->getqvw(curstate);

		reward = actionList->getAction(act+1)->reward(curstate);

		qvw->updateqval(act, nqvw, reward, discount);

		qvw = nqvw;
	}				

	if (tree->qvw->visits < maxVisits / 2) 
		return itercount;

	itercount = 0;
	curstate = state();
	curstate.setData(stateData);
	curstate.buildcomps();
	
	qvw = tree->getqvw(curstate);

	terminate = false;

	while (!terminate && (qvw->bestact != NOOP) && itercount < 2*maxIterations) 
	{
		itercount++;
		terminate = transition(qvw->bestact, curstate);

		qvalweb *nqvw = tree->getqvw(curstate);

		int act = qvw->bestact;

		reward = actionList->getAction(act+1)->reward(curstate);

		qvw->updateqval(qvw->bestact, nqvw, reward, discount);

		qvw = nqvw;
	}

	return itercount;
}

// treesort - resorts the qvaltree.

int Agent::treesort(state &curstate, qvaltree *tree, bool show) 
{
	int itercount = actionList->getNumberActions() * actionList->getNumberActions() * curstate.getData().list.size() * curstate.getData().list.size() + 1;

	int score = 0;

	if (show)
	{
		cout << curstate.showData() << endl;
		cout << curstate.tostring() << endl;
	}

	bool terminate = false;

	while (!terminate) 
	{
		itercount--;
		if (itercount < 0) 
			return -1;

		qvalweb *qvw = tree->getqvw(curstate);

		qvw->visited = true;

		if (qvw->bestact == NOOP) 
			break;

		terminate = transition(qvw->bestact, curstate);
		
		if (show) 
		{
			cout << curstate.tostring() << "\t"; 
			cout << actionList->getAction(qvw->bestact+1)->getDescription();
			cout << endl;
		}

		if (qvw->bestact == SWAP) 
			score++;

		qvalweb *nqvw = tree->getqvw(curstate);
	}

	if (!curstate.isFinished()) 
		return -1;

	return score;
}

// set Discount, MaxIterations, MaxIterationCount, MaxVisits, setReportCount
// sets RP specific values for calculating Q-Values.

void Agent::setDiscount(double discount)
{
    this->discount = discount;
}

void Agent::setMaxIterations(int maxIter)
{
	maxIterations = maxIter;
}

void Agent::setMaxIterationCount(int maxCount)
{
	maxIterationCount = maxCount;
}

void Agent::setMaxVisits(int maxVisits)
{
	this->maxVisits = maxVisits;
}

void Agent::setReportCount(int repCount)
{
	reportCount = repCount;
}

// run - calculates a policy based on the training states provided.

bool Agent::run() 
{
	long srseed = time(NULL);
	
	srand(srseed);
	
	vector< state* > trainStates;
	trainStates.reserve(trainingStates.size());
	trainStates.push_back(trainingStates[trainingStates.size() - 1]);

	tree = NULL;
	
	bool failure = true;
	
	int itercount = 0;

	while (failure && itercount < maxIterationCount)
	{
		failure = false;
		for (int i = 0; i < trainStates.size(); i++) 
		{		
			state s = *trainStates[i];				
				
			if (tree == NULL) 
			{
				tree = new qvaltree(s, actionList);
			}
			else 
				tree->getqvw(s);
		}
	
		bool notmaxed = true;
	
		int reportscore = 0;

		while (notmaxed) 
		{
			itercount++;
	
			notmaxed = false;

			for (int i = 0; i < trainStates.size(); i++)
			{
				
				state s = *trainStates[i];
				qvalweb *qvw = tree->getqvw(s);
					
				reportscore += learn(s, tree);
					
				if (qvw->visits < maxVisits)
					notmaxed = true;
						
				if (qvw->visits < maxVisits && itercount % reportCount == 0) 
				{
					cout << itercount << "\t" << (i+1) << " / ";
					cout << trainStates.size() << "\t";
					cout << s.showData() << "\t";
					cout << qvw->visits << "\t" << qvw->qval << "\t";
					cout << actionList->getAction(qvw->bestact+1)->getDescription();
					cout << "\t" << tree->number << endl;
				}
			}
	
			if (itercount % reportCount == 0) 
			{
				reportscore = reportscore / (reportCount * trainStates.size());
				cout << "avg iters:\t" << reportscore << endl << endl;
		 		reportscore = 0;
			}
		} 

		for (int i = 0; i < trainStates.size(); i++) 
		{
			state temp = *trainStates[i];
			
			if (treesort(temp, tree, true) < 0) 
			{
				failure = true;
				tree->clearvisits();
				break;
			}
		}

		if (!failure) 
		{
			tree->clearvisits();			
			trainStates.clear();
			for (int i = 0; i < trainingStates.size(); i++)
			{
				state temp = *trainingStates[i];
				
				if (treesort(temp, tree, true) < 0) 
				{
					trainStates.push_back(trainingStates[i]);
					failure = true;
					cout << "failure on:\t" << i << endl;
					i = trainingStates.size();
				}
			}
		}
		else
			continue;

		if (failure) 
		{
			tree->clearvisits();
			tree->clearvisited();
		}
	}

	if (itercount >= maxIterationCount) 
	{
		cerr << "FAILURE TO CONVERGE" << endl;
		cerr << discount << endl; 
		delete tree;
		return false;
	}
	
	return true;
}

// printReport -- Prints the policy report generated by the agent.

void Agent::printReport()
{	
	vector<qvalweb*> qvws = tree->getqvws();
	
	int depth, leaf;

	cout << "TREE" << endl;
	tree->showtree(true);
	
	cout << "BUILDING EDT" << endl;
	
	edt *etree = new edt(qvws, depth, leaf, 0, actionList);
	
	etree->showedt();
	cout << "depth = " << depth << endl;
	cout << "leaves = " << leaf << endl;
		
	delete etree;
	delete tree;
}
