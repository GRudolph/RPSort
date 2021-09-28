#ifndef __STATE_H__
#define __STATE_H__

#include "usefullibs.h"
#include "usefulfunc.h"

// dataStructure
//
// This is the user defined data.

struct dataStructure
{
	int i;
	int j;
	int k;
	int distance;
	vector<int> list;
};

// conditionalStructure
//
// This is the user defined conditions associated with the data.  It is
// used by the agent to determine the current state, and if two states are
// equivalent.

struct conditionalStructure
{
	bool izero;
	bool jzero;
	bool kzero;
	bool ilen;
	bool jlen;
	bool klen;
	bool iltj;
	bool iltk;
	bool igtj;
	bool igtk;
	bool jltk;
	bool jgtk;

	bool sorted;
	bool distance_test;
};

// state
//
// Maintains user-defined state and conditional info, and functions to modify
// these.

class state {
private:
	int lastActionID;
	int numberComparisons;
	
	conditionalStructure conditions;
	
public:

	dataStructure data;

	state();
	state(state &s);
	state(vector<int> &l);

	bool operator==(state &rhs);
	bool operator!=(state &rhs);
	bool operator>(state &rhs);
	bool operator<(state &rhs);

	bool isgoal() {return conditions.distance_test;}
	
	bool isFinished();

	string tostring();
	string showData();
	void buildcomps();
	
	int getLastActionID();
	void setLastActionID(int);
	
	bool getComparison(int comparisonNumber);
	int getNumberComparisons();
	string getComparisonDescription(int comparisonNumber);
	
	dataStructure getData();
	void setData(dataStructure data);
	
	conditionalStructure getConditions();
	conditionalStructure setConditions(conditionalStructure conditions);
};

#endif
