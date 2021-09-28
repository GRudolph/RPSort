#ifndef __QVALWEB_H__
#define __QVALWEB_H__

#include "state.h"
#include "ActionList.h"

// qvalweb
//
// This class is a node in the qvaltree, and contains the Q-value for a 
// particular state/action pair.

class qvalweb 
{
private:
	ActionList* actionList;
public:

	state s;
	int bestact;
	int baindex;

	double qval;

	int visits;
	bool visited;

	vector<int> actions;
	vector<int> actcount;

	vector< vector<qvalweb*> > qvws;
	vector< vector<int> > qvwcount;

	vector< vector<int> > rewards;
	vector< vector<int> > rewardcount;

	vector<double> qvals;

	qvalweb(state _s, ActionList* actionList);
	void updateqval(int a, qvalweb *qvw, int reward, double DISCOUNT);
};

#endif
