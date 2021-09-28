#include "state.h"

state::state() 
{
	int NOOP = -1;

	data.i = 0; 
	data.j = 0; 
	data.k = 0;	
	data.distance = 0;
	
	lastActionID = NOOP; 
	
	conditions.izero = true;
	conditions.jzero = true;
	conditions.kzero = true;
	conditions.sorted = true;
	conditions.ilen = false;
	conditions.jlen = false;
	conditions.klen = false;
	conditions.igtj = false;
	conditions.iltj = false;
	conditions.igtk = false;
	conditions.iltk = false;
	conditions.jltk = false;
	conditions.jgtk = false;
	conditions.distance_test = true;
}


state::state(vector<int> &l) 
{
	int NOOP = -1;

	data.list = l;
	data.i = 0;
	data.j = 0;
	data.k = 0;
	
	lastActionID = NOOP; 
	buildcomps();

	data.distance = 0;
}

state::state(state &s) {
	data.i = s.getData().i;
	data.j = s.getData().j;
	data.k = s.getData().k;
	
	lastActionID = s.getLastActionID();
	
	conditions.izero = s.conditions.izero;
	conditions.jzero = s.conditions.jzero;
	conditions.kzero = s.conditions.kzero;
	conditions.ilen = s.conditions.ilen;
	conditions.jlen = s.conditions.jlen;
	conditions.klen = s.conditions.klen;
	conditions.igtj = s.conditions.igtj;
	conditions.iltj = s.conditions.iltj;
	conditions.igtk = s.conditions.igtk;
	conditions.iltk = s.conditions.iltk;
	conditions.jgtk = s.conditions.jgtk;
	conditions.jltk = s.conditions.jltk;
	conditions.sorted = s.conditions.sorted;
	
	data.list = s.getData().list;
	
	data.distance = s.getData().distance;
	conditions.distance_test = s.conditions.distance_test;
}

bool state::operator==(state &rhs) {
	if (lastActionID != rhs.getLastActionID()) return false;
	if (conditions.izero != rhs.conditions.izero) return false;
	if (conditions.jzero != rhs.conditions.jzero) return false;
	if (conditions.kzero != rhs.conditions.kzero) return false;
	if (conditions.ilen != rhs.conditions.ilen) return false;
	if (conditions.jlen != rhs.conditions.jlen) return false;
	if (conditions.klen != rhs.conditions.klen) return false;
	if (conditions.igtj != rhs.conditions.igtj) return false;
	if (conditions.iltj != rhs.conditions.iltj) return false;
	if (conditions.igtk != rhs.conditions.igtk) return false;
	if (conditions.iltk != rhs.conditions.iltk) return false;
	if (conditions.jgtk != rhs.conditions.jgtk) return false;
	if (conditions.jltk != rhs.conditions.jltk) return false;
	if (conditions.sorted != rhs.conditions.sorted) return false;
	if (data.distance == 0 && rhs.getData().distance != 0) return false;
	if (data.distance != 0 && rhs.getData().distance == 0) return false;

	return true;
}

bool state::operator!=(state &rhs) {
	if (lastActionID != rhs.getLastActionID()) return true;
	if (conditions.izero != rhs.conditions.izero) return true;
	if (conditions.jzero != rhs.conditions.jzero) return true;
	if (conditions.kzero != rhs.conditions.kzero) return true;
	if (conditions.ilen != rhs.conditions.ilen) return true;
	if (conditions.jlen != rhs.conditions.jlen) return true;
	if (conditions.klen != rhs.conditions.klen) return true;
	if (conditions.igtj != rhs.conditions.igtj) return true;
	if (conditions.iltj != rhs.conditions.iltj) return true;
	if (conditions.igtk != rhs.conditions.igtk) return true;
	if (conditions.iltk != rhs.conditions.iltk) return true;
	if (conditions.jgtk != rhs.conditions.jgtk) return true;
	if (conditions.jltk != rhs.conditions.jltk) return true;
	if (conditions.sorted != rhs.conditions.sorted) return true;
	if (data.distance == 0 && rhs.getData().distance != 0) return true;
	if (data.distance != 0 && rhs.getData().distance == 0) return true;

	return false;
}

bool state::operator>(state &rhs) {
	if (lastActionID > rhs.getLastActionID()) return true;
	if (lastActionID != rhs.getLastActionID()) return false;

	if (conditions.izero && !rhs.conditions.izero) return true;
	if (conditions.izero != rhs.conditions.izero) return false;

	if (conditions.ilen && !rhs.conditions.ilen) return true;
	if (conditions.ilen != rhs.conditions.ilen) return false;

	if (conditions.jzero && !rhs.conditions.jzero) return true;
	if (conditions.jzero != rhs.conditions.jzero) return false;

	if (conditions.jlen && !rhs.conditions.jlen) return true;
	if (conditions.jlen != rhs.conditions.jlen) return false;

	if (conditions.kzero && !rhs.conditions.kzero) return true;
	if (conditions.kzero != rhs.conditions.kzero) return false;

	if (conditions.klen && !rhs.conditions.klen) return true;
	if (conditions.klen != rhs.conditions.klen) return false;

	if (conditions.iltj && !rhs.conditions.iltj) return true;
	if (conditions.iltj != rhs.conditions.iltj) return false;

	if (conditions.igtj && !rhs.conditions.igtj) return true;
	if (conditions.igtj != rhs.conditions.igtj) return false;

	if (conditions.iltk && !rhs.conditions.iltk) return true;
	if (conditions.iltk != rhs.conditions.iltk) return false;

	if (conditions.igtk && !rhs.conditions.igtk) return true;
	if (conditions.igtk != rhs.conditions.igtk) return false;

	if (conditions.jltk && !rhs.conditions.jltk) return true;
	if (conditions.jltk != rhs.conditions.jltk) return false;

	if (conditions.jgtk && !rhs.conditions.jgtk) return true;
	if (conditions.jgtk != rhs.conditions.jgtk) return false;

	if (conditions.sorted && !rhs.conditions.sorted) return true;
	if (conditions.sorted != rhs.conditions.sorted) return false;

	if (data.distance != 0 && rhs.getData().distance == 0) return true;
	if (data.distance == 0 && rhs.getData().distance != 0) return false;

	return false;
}

bool state::operator<(state &rhs) {
	if (lastActionID < rhs.getLastActionID()) return true;
	if (lastActionID != rhs.getLastActionID()) return false;

	if (!conditions.izero && rhs.conditions.izero) return true;
	if (conditions.izero != rhs.conditions.izero) return false;

	if (!conditions.ilen && rhs.conditions.ilen) return true;
	if (conditions.ilen != rhs.conditions.ilen) return false;

	if (!conditions.jzero && rhs.conditions.jzero) return true;
	if (conditions.jzero != rhs.conditions.jzero) return false;

	if (!conditions.jlen && rhs.conditions.jlen) return true;
	if (conditions.jlen != rhs.conditions.jlen) return false;

	if (!conditions.kzero && rhs.conditions.kzero) return true;
	if (conditions.kzero != rhs.conditions.kzero) return false;

	if (!conditions.klen && rhs.conditions.klen) return true;
	if (conditions.klen != rhs.conditions.klen) return false;

	if (!conditions.iltj && rhs.conditions.iltj) return true;
	if (conditions.iltj != rhs.conditions.iltj) return false;

	if (!conditions.igtj && rhs.conditions.igtj) return true;
	if (conditions.igtj != rhs.conditions.igtj) return false;

	if (!conditions.iltk && rhs.conditions.iltk) return true;
	if (conditions.iltk != rhs.conditions.iltk) return false;

	if (!conditions.igtk && rhs.conditions.igtk) return true;
	if (conditions.igtk != rhs.conditions.igtk) return false;

	if (!conditions.jltk && rhs.conditions.jltk) return true;
	if (conditions.jltk != rhs.conditions.jltk) return false;

	if (!conditions.jgtk && rhs.conditions.jgtk) return true;
	if (conditions.jgtk != rhs.conditions.jgtk) return false;

	if (!conditions.sorted && rhs.conditions.sorted) return true;
	if (conditions.sorted != rhs.conditions.sorted) return false;

	if (data.distance == 0 && rhs.getData().distance != 0) return true;
	if (data.distance != 0 && rhs.getData().distance == 0) return false;

	return false;
}

string state::tostring() 
{
	string result = "!aCtIoN!";
	
//	Action* action = actionList->getAction(lastActionID + 1);
	
//	result = actionList->getAction(lastActionID + 1)->getDescription();

	result += "\t";

	if (conditions.izero) {
		result += "i=0";
	} else if (conditions.ilen) {
		result += "i=len";
	} else result += "i=?";

	result += "\t";

	if (conditions.jzero) {
		result += "j=0";
	} else if (conditions.jlen) {
		result += "j=len";
	} else result += "j=?";

	result += "\t";

	if (conditions.kzero) {
		result += "k=0";
	} else if (conditions.klen) {
		result += "k=len";
	} else result += "k=?";

	result += "\t";

	if (conditions.iltj) {
		result += "i<j";
	} else if (conditions.igtj) {
		result += "i>j";
	} else result += "i=j";

	result += "\t";

	if (conditions.iltk) {
		result += "i<k";
	} else if (conditions.igtk) {
		result += "i>k";
	} else result += "i=k";

	result += "\t";

	if (conditions.jltk) {
		result += "j<k";
	} else if (conditions.jgtk) {
		result += "j>k";
	} else result += "j=k";

	result += "\t";

	if (conditions.sorted) {
		result += "L[i] <= L[j]";
	} else result += "L[i] > L[j]";

	result += "\t";

	result += itoa(data.distance);

	return result;
}

string state::showData()
{
	string result = itoa(data.list[0]);
	for (int i = 1; i < data.list.size(); i++) result = result + "\t" + itoa(data.list[i]);

	return result;
}

void state::buildcomps() {
	conditions.izero = (data.i == 0);
	conditions.jzero = (data.j == 0);
	conditions.kzero = (data.k == 0);
	conditions.ilen = (data.i == data.list.size());
	conditions.jlen = (data.j == data.list.size());
	conditions.klen = (data.k == data.list.size());
	conditions.iltj = (data.i < data.j);
	conditions.igtj = (data.i > data.j);
	conditions.iltk = (data.i < data.k);
	conditions.igtk = (data.i > data.k);
	conditions.jltk = (data.j < data.k);
	conditions.jgtk = (data.j > data.k);
	conditions.distance_test = (data.distance == 0);

	if (data.i == data.list.size() || data.j == data.list.size()) {
		conditions.sorted = true;
	} else conditions.sorted = (data.list[data.i] <= data.list[data.j]);

	conditions.iltk = false; conditions.igtk = false;
	conditions.jltk = false; conditions.jgtk = false;
}

int state::getLastActionID()
{
	return lastActionID;
}

void state::setLastActionID(int ID)
{
    lastActionID = ID;
}

bool state::getComparison(int comparisonNumber)
{
	switch (comparisonNumber)
	{
		case 1:
			return conditions.izero;
			break;
		case 2:
			return conditions.jzero;
			break;
		case 3:
			return conditions.kzero;
			break;
		case 4:
			return conditions.ilen;
			break;
		case 5:
			return conditions.jlen;
			break;
		case 6:
			return conditions.klen;
			break;
		case 7:
			return conditions.iltj;
			break;
		case 8:
			return conditions.igtj;
			break;
		case 9:
			return conditions.iltk;
			break;
		case 10:
			return conditions.igtk;
			break;
		case 11:
			return conditions.jltk;
			break;
		case 12:
			return conditions.jgtk;
			break;
		case 13:
			return conditions.sorted;
			break;
		case 14:
			return conditions.distance_test;
			break;
		default:
			return false;
	}
}

int state::getNumberComparisons()
{
	return numberComparisons;
}

string state::getComparisonDescription(int comparisonNumber)
{
	string results;

	switch (comparisonNumber)
	{
		case 1:
			results = "i==0";
			break;
		case 2:
			results = "j==0";
			break;
		case 3:
			results = "k==0";
			break;
		case 4:
			results = "i==len";
			break;
		case 5:
			results = "j==len";
			break;
		case 6:
			results = "k==len";
			break;
		case 7:
			results = "i<j";
			break;
		case 8:
			results = "i>j";
			break;
		case 9:
			results = "i<k";
			break;
		case 10:
			results = "i>k";
			break;
		case 11:
			results = "j<k";
			break;
		case 12:
			results = "j>k";
			break;
		case 13:
			results = "sorted(list, i, j)";
			break;
		case 14:
			results = "finished";
			break;
		default:
			results = "ERROR!";
			break;
	}
	
	return results;
}

dataStructure state::getData()
{
	return this->data;
}

void state::setData(dataStructure data)
{
	this->data = data;
}

bool state::isFinished()
{	
	bool results = true;
	
	// Check if the list is sorted
	
	for (int i = 0; i < data.list.size()-1; i++) 
	{
		if (data.list[i] > data.list[i+1]) 
			results = false;
	}

	results = results && isgoal();		// Dunno why...

	return results;
} 

conditionalStructure state::getConditions()
{
	return conditions;
}

conditionalStructure state::setConditions(conditionalStructure c)
{
	conditions = c;
}
