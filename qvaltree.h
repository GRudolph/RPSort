#ifndef __QVALTREE_H__
#define __QVALTREE_H__

#include "state.h"
#include "ActionList.h"
#include "qvalweb.h"

// qvaltree
//
// qvaltree maintains the graph of potential paths an agent may use to generate
// the policy.  This is later trimmed to get the ideal path.

class qvaltree {
private:
	ActionList* actionList;
public:
	qvaltree(state &s, ActionList* actionList);
	~qvaltree();

	qvalweb* getqvw(state &s);

	void clearvisits();
	void clearvisited();

	void showtree(bool masked);

	vector<qvalweb*> getqvws();
	vector<qvalweb*> getallqvws();

	int number;

	qvalweb *qvw;
	qvaltree *left;
	qvaltree *right;
};

#endif

