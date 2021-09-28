#include "edt.h"

// Constructor -- creates a policy to be printed out by showedt.  

edt::edt(vector<qvalweb*> &qvws, int &depth, int &leaf, int pd, ActionList* actionList) 
{
	this->actionList = actionList;
	
	int numberComparisons = qvws[0]->s.getNumberComparisons();

	int NOOP = -1;
	int temp_action;

	{
		bool pureset = true;
		int act2 = qvws[0]->bestact;
		for (int i = 1; i < qvws.size(); i++) 
		{
		    if (qvws[i]->bestact != act2) 
		    {
			    pureset = false;
			    break;
			}
		}

		if (pureset) 
		{
			depth = 0;
			leaf = 1;
			which = -1;
			act = act2;

			return;
		}
	}

	int minleaf = INT_MAX;
	int mindepth = INT_MAX;
	which = -1;
	act = NOOP;

	children = vector<edt*>(0);

	{ // lastact
		vector<int> tempacts(0);
		tempacts.reserve(qvws.size());
		for (int i = 0; i < qvws.size(); i++) 
		{
			bool found = false;
			for (int j = 0; j < tempacts.size(); j++) 
			{
				if (tempacts[j] == qvws[i]->s.getLastActionID()) 
				{
					found = true;
					break;
				}
			}

			if (!found) 
			{
			    temp_action = NOOP;
			    temp_action = qvws[i]->s.getLastActionID();
			    tempacts.push_back(temp_action);
			}
		}

		if (tempacts.size() > 1) 
		{
			vector< vector<qvalweb*> > qvws2(0);
			qvws2.reserve(tempacts.size());
			
			for (int i = 0; i < tempacts.size(); i++) 
			{
				vector<qvalweb*> temp(0);
				temp.reserve(qvws.size());
				for (int j = 0; j < qvws.size(); j++) 
				{
					if (qvws[j]->s.getLastActionID() == tempacts[i])
					{
					    temp.push_back(qvws[j]);
					}
				}
				qvws2.push_back(temp);
			}

			int maxdepth = 0;
			int maxleaf = 0;
			vector<edt*> temp(0);
			temp.reserve(tempacts.size());

			for (int i = 0; i < qvws2.size(); i++) 
			{
				int wdepth;
				int wleaf;
				temp.push_back(new edt(qvws2[i], wdepth, wleaf, pd + 1, actionList));
				maxleaf += wleaf;
				
				if (wdepth > maxdepth) 
					maxdepth = wdepth;
			}

			if (maxleaf < minleaf) 
			{
				minleaf = maxleaf;
				mindepth = maxdepth;
				which = LASTACT;
				
				for (int i = 0; i < children.size(); i++) 
					delete children[i];
					
				actions = tempacts;
				children = temp;
			} 
			else if (maxleaf == minleaf) 
			{
				if (maxdepth < mindepth) 
				{
					mindepth = maxdepth;
					which = LASTACT;
					
					for (int i = 0; i < children.size(); i++) 
						delete children[i];
					actions = tempacts;
					children = temp;
				} 
				else
				{
					for (int i = 0; i < temp.size(); i++) 
						delete temp[i];
				}
			} 
			else
			{
				for (int i = 0; i < temp.size(); i++) 
					delete temp[i];
			}
		}
	}
	
	for(int i=1; i<=numberComparisons; i++)
	{
		edtloop(qvws, pd, minleaf, mindepth, i);
	}

	leaf = minleaf;
	depth = mindepth + 1;
}

edt::~edt() 
{
	for (int i = 0; i < children.size(); i++) delete children[i];
}

int edt::getact(state &s) 
{
	int NOOP = -1;
	
	if (which >= 0 || act != NOOP) return act;

	int cindex = -1;

	if(which == LASTACT)
	{
		for (int i = 0; i < actions.size(); i++)
		{
			if (s.getLastActionID() == actions[i]) 
			{
				cindex = i;
				break;
			}
		}
	}
	else if(which > 0 && which <= s.getNumberComparisons())
	{
		if(s.getComparison(which))
		{
			cindex = 1;
		}
		else
		{
			cindex = 0;
		}
	}
	else
	{
		cindex = -1;
	}

	if (cindex < 0) return act;

	return children[cindex]->getact(s);
}

// These two function print out the report generated.

void edt::showedt() {
	showedt(0);
}

void edt::showedt(int level)
{	
	state s;

	int NOOP = -1;

	if (act != NOOP || which < 0) 
	{
		for (int i = 0; i < level; i++) cout << "\t";
		cout << actionList->getAction(act+1)->getDescription() << endl;
		return;
	}

	if(which==LASTACT)
	{
		for (int i = 0; i < actions.size(); i++) 
		{
			for (int j = 0; j < level; j++) 
				cout << "\t";
			
			cout << "lastact == ";
			cout << actionList->getAction(actions[i]+1)->getDescription();
			cout << endl;
			
			children[i]->showedt(level+1);
		}
	}
	else
	{
		for (int i = 0; i < level; i++)
			cout << "\t";
		
		cout << "if (" << s.getComparisonDescription(which) << ")\n";
		
		for (int i = 0; i < level; i++)
			cout << "\t";
			
		cout << "{\n";
		
		children[1]->showedt(level+1);
		
		for (int i = 0; i < level; i++)
			cout << "\t";
			
		cout << "}\n";
		
		for (int i = 0; i < level; i++)
			cout << "\t";
		
		cout << "else\n";
		
		for (int i = 0; i < level; i++)
			cout << "\t";
		
		cout << "{\n";
		
		children[0]->showedt(level+1);
		
		for (int i = 0; i < level; i++)
			cout << "\t";
		
		cout << "}\n";
	}
}

void edt::edtloop(vector<qvalweb*> &qvws, int &pd, int &minleaf, int &mindepth, int compareNumber)
{
	vector<qvalweb*> zeros(0);
	zeros.reserve(qvws.size());
	vector<qvalweb*> ones(0);
	ones.reserve(qvws.size());
	int maxdepth = 0;
	int maxleaf = 0;
	int wdepth, wleaf;


	for (int i = 0; i < qvws.size(); i++) 
	{
		if (!qvws[i]->s.getComparison(compareNumber))
			zeros.push_back(qvws[i]); 
		else 
			ones.push_back(qvws[i]);
	}

	if (zeros.size() != 0 && ones.size() != 0) 
	{
		vector<edt*> temp(0);
		temp.reserve(2);
		temp.push_back(new edt(zeros, wdepth, wleaf, pd+1, actionList));
		maxleaf += wleaf;
		
		if (wdepth > maxdepth) 
			maxdepth = wdepth;
			
		temp.push_back(new edt(ones, wdepth, wleaf, pd+1, actionList));
		maxleaf += wleaf;
		
		if (wdepth > maxdepth) 
			maxdepth = wdepth;

		if (maxleaf < minleaf) 
		{
			minleaf = maxleaf;
			mindepth = maxdepth;
			which = compareNumber;
				
			for (int i = 0; i < children.size(); i++) 
				delete children[i];
			children = temp;
		} 
		else if (maxleaf == minleaf) 
		{
			if (maxdepth < mindepth) 
			{
				mindepth = maxdepth;
				which = compareNumber;
				
				for (int i = 0; i < children.size(); i++) 
					delete children[i];
				children = temp;
			} 
			else 
			{
				delete temp[0];
				delete temp[1];
			}
		} 
		else 
		{
			delete temp[0];
			delete temp[1];
		}
	}
}


