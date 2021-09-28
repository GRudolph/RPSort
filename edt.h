#ifndef __EDT_H__
#define __EDT_H__

#include "state.h"
#include "qvalweb.h"

// edt
//
// The edt class creates and displays the generated policy from the qvaltree

class edt {
public:
	static const int LASTACT = 0;

	edt(vector<qvalweb*> &qvws, int &depth, int &leaf, int pd, ActionList* actionList);
	~edt();

	int getact(state &s);
	void showedt();
	
	int which;
	int act;
	vector<edt*> children;
	vector<int> actions;

private:
	void showedt(int level);
	void edtloop(vector<qvalweb*> &qvws, int &pd, int &minleaf, int &mindepth, int compareNumber);
	ActionList* actionList;
};

#endif
