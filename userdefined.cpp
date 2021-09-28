
#include "state.h"
#include "usefullibs.h"
//#include "Action.h"

bool issorted2(vector<int> &list) {
	for (int i = 0; i < list.size()-1; i++) if (list[i] > list[i+1]) return false;
	return true;
}

// Below are all user defined actions.

bool NOOPaction(state &curstate) 
{
    return false; 
}

bool NOOPcanAct(state &curstate)
{
    return true;
}

int NOOPreward(state &curstate)
{
	return 0;
}

bool INCIaction(state &curstate) 
{ 
	curstate.data.i++;
	if (curstate.data.i > curstate.data.list.size()) 
		curstate.data.i = curstate.data.list.size();

    return false; 
}

bool INCIcanAct(state &curstate)
{
    return curstate.data.i != curstate.data.list.size();
}

int INCIreward(state &curstate)
{
	return 0;
}

bool INCJaction(state &curstate) 
{ 
	curstate.data.j++;
	if (curstate.data.j > curstate.data.list.size()) 
	    curstate.data.j = curstate.data.list.size();

    return false; 
}

bool INCJcanAct(state &curstate)
{
    return curstate.data.j != curstate.data.list.size();
}

int INCJreward(state &curstate)
{
	return 0;
}

bool INCKaction(state &curstate) 
{ 
	curstate.data.k++;
	if (curstate.data.k > curstate.data.list.size()) 
		curstate.data.k = curstate.data.list.size();

    return false; 
}

bool INCKcanAct(state &curstate)
{
    return curstate.data.k != curstate.data.list.size();
}

int INCKreward(state &curstate)
{
	return 0;
}

bool SETIZEROaction(state &curstate) 
{ 
	curstate.data.i = 0;
	if (curstate.getLastActionID() == 3) //SETJZERO)
	    curstate.data.distance = 0;

    return false; 
}

bool SETIZEROcanAct(state &curstate)
{
    return curstate.data.i != 0;
}

int SETIZEROreward(state &curstate)
{
	return 0;
}

bool SETJZEROaction(state &curstate) 
{
	curstate.data.j = 0;
	if (curstate.getLastActionID() == 2) //SETIZERO) 
		curstate.data.distance = 0;

    return false; 
}

bool SETJZEROcanAct(state &curstate)
{
    return curstate.data.j != 0;
}

int SETJZEROreward(state &curstate)
{
	return 0;
}

bool SETKZEROaction(state &curstate) 
{
	curstate.data.k = 0;

    return false; 
}

bool SETKZEROcanAct(state &curstate)
{
    return curstate.data.k != 0;
}

int SETKZEROreward(state &curstate)
{
	return 0;
}

bool SWAPaction(state &curstate) 
{
	if (curstate.data.j < curstate.data.list.size() && 
		curstate.data.i < curstate.data.list.size())
	{
		int temp = curstate.data.list[curstate.data.i];
		int temp2 = curstate.data.list[curstate.data.j];
		curstate.data.list[curstate.data.i] = curstate.data.list[curstate.data.j];
		curstate.data.list[curstate.data.j] = temp;
	}

    return false; 
}

bool SWAPcanAct(state &curstate)
{
    return true;
}

int SWAPreward(state &curstate)
{
	int SWAPREWARD = 40;
	int SWAPPENALTY = -40;

	int reward = 0;

	if (curstate.data.i == curstate.data.j || curstate.getConditions().ilen || curstate.getConditions().jlen)
	{
		reward = SWAPPENALTY;
	}
	else if (!curstate.getConditions().sorted || curstate.getConditions().igtj)
	{
		reward = SWAPPENALTY;
	}
	else
	{
		reward = SWAPREWARD;
	}
	
	return reward;
}

bool TERMINATEaction(state &curstate) 
{ 
    return true; 
}

bool TERMINATEcanAct(state &curstate)
{
    return drand48() < 0.9;
}

int TERMINATEreward(state &curstate)
{

	int TERMREWARD = 400;
	int TERMPENALTY = -400;

	int reward = 0;

	if (curstate.isgoal() && issorted2(curstate.data.list))
	{
		reward = TERMREWARD;
	}
	else
	{
		reward = TERMPENALTY;
	}
	
	return reward;
}


