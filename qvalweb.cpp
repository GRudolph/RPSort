#include "qvalweb.h"

qvalweb::qvalweb(state _s, ActionList* actionList) 
{
	this->actionList = actionList;

	int NOOP = -1;

	s = _s;
	bestact = NOOP;
	baindex = -1;
	qval = 0;

	visited = 0;
	visited = false;

	actions = vector<int>(0);
	actions.reserve(actionList->getNumberActions());

	actcount = vector<int>(0);
	actcount.reserve(actionList->getNumberActions());

	qvws = vector< vector<qvalweb*> >(0);
	qvws.reserve(actionList->getNumberActions());

	qvwcount = vector< vector<int> >(0);
	qvwcount.reserve(actionList->getNumberActions());

	rewards = vector< vector<int> >(0);
	rewards.reserve(actionList->getNumberActions());

	rewardcount = vector< vector<int> >(0);
	rewardcount.reserve(actionList->getNumberActions());

	qvals = vector<double>(0);
	qvals.reserve(actionList->getNumberActions());
}

void qvalweb::updateqval(int a, qvalweb *qvw, int reward, double DISCOUNT) 
{
	int NOOP = -1;
	
//	if (s.isgoal()) return;

	int aindex = -1;

	for (int i = 0; i < actions.size(); i++) 
	{
	    if (actions[i] == a) 	// Can this be avoided?
	    {
		    aindex = i;
		    break;
	    }
	}

	if (aindex < 0) 
	{
		actions.push_back(a);
		actcount.push_back(1);

		vector<int> temp(0);
		temp.push_back(reward);
		rewards.push_back(temp);

		temp[0] = 1;
		rewardcount.push_back(temp);

		qvwcount.push_back(temp);

		vector<qvalweb*> temp2(0);
		temp2.push_back(qvw);
		qvws.push_back(temp2);

		qvals.push_back(0);
	}
	else 
	{
		actcount[aindex]++;

		int index = -1;
		for (int i = 0; i < rewards[aindex].size(); i++) 
		{
			if (rewards[aindex][i] == reward) 
			{
				index = i;
				break;
			}
		}

		if (index < 0) 
		{
			rewards[aindex].push_back(reward);
			rewardcount[aindex].push_back(1);
		}
		else 
			rewardcount[aindex][index]++;

		index = -1;
		
		for (int i = 0; i < qvws[aindex].size(); i++)
		{
			if (qvws[aindex][i] == qvw) 
			{
				index = i;
				break;
			}
		}

		if (index < 0) 
		{
			qvws[aindex].push_back(qvw);
			qvwcount[aindex].push_back(1);
		}
		else 
			qvwcount[aindex][index]++;
	}

	for (int i = 0; i < qvals.size(); i++) 
	{
		double rtemp = 0;
		for (int j = 0; j < rewards[i].size(); j++)
		{
			rtemp = rtemp + ((double)rewards[i][j]) * ((double)rewardcount[i][j]) / ((double)actcount[i]);
		}

		double qtemp = 0;
		
		for (int j = 0; j < qvws[i].size(); j++) 
		{
			if (qvws[i][j]->s == s) 
			{
				qtemp = -(HUGE_VAL/2.0);
				break;
			}
			else
				qtemp = qtemp + (qvws[i][j]->qval) * ((double)qvwcount[i][j]) / ((double)actcount[i]);
		}

		if (qtemp > 0) 
			qtemp *= DISCOUNT;
		if (qtemp < 0) 
			qtemp = qtemp * (1.0 + DISCOUNT);

		qvals[i] = rtemp + qtemp;
	}

	if (bestact==NOOP || baindex < 0) 
	{
		qval = 0;
		baindex = -1;
		bestact = NOOP;
	}
	else qval = qvals[baindex];

	int oldindex = baindex;

	for (int i = 0; i < qvals.size(); i++) 
	{
		if (baindex < 0 || qvals[i] > qval) 
		{
			qval = qvals[i];
			baindex = i;
		}
	}

	if (baindex >= 0) 
		bestact = actions[baindex];

	if (oldindex == baindex && baindex >= 0) 
		visits++;
}
