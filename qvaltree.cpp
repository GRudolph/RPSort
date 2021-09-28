#include "qvaltree.h"

qvaltree::qvaltree(state &s, ActionList* actionList) 
{
	this->actionList = actionList;

	qvw = new qvalweb(s, actionList);
	left = NULL;
	right = NULL;
	number = 1;
}

qvaltree::~qvaltree() 
{
	delete left;
	delete right;
	delete qvw;
}

qvalweb* qvaltree::getqvw(state &s) 
{
	qvaltree *head = this;
	qvaltree *tail = NULL;

	while (head != NULL && tail != head) {
		tail = head;
		if (s < (head->qvw->s)) {
			head = head->left;
		} else if (s > (head->qvw->s)) {
			head = head->right;
		}
	}

	if (head != NULL) return head->qvw;

	number++;

	if (s < tail->qvw->s) {
		tail->left = new qvaltree(s, actionList);
		return tail->left->qvw;
	} else {
		tail->right = new qvaltree(s, actionList);
		return tail->right->qvw;
	}
}

void qvaltree::clearvisits() 
{
	if (left != NULL) left->clearvisits();
	if (right != NULL) right->clearvisits();
	qvw->visits = 0;
}

void qvaltree::clearvisited() 
{
	if (left != NULL) left->clearvisited();
	if (right != NULL) right->clearvisited();
	qvw->visited = false;
}

void qvaltree::showtree(bool masked) 
{
    Action* action = actionList->getAction(qvw->bestact + 1);

	if (left != NULL) left->showtree(masked);
	if (qvw->visited || !masked) 
	{
		cout << qvw->s.tostring() << "\t" << action->getDescription() << "\t" << qvw->qval << endl;

	}
	if (right != NULL) right->showtree(masked);
}

vector<qvalweb*> qvaltree::getqvws() 
{
	vector<qvalweb*> results(0);
	vector<qvalweb*> leftr(0);
	vector<qvalweb*> rightr(0);

	if (left != NULL) leftr = left->getqvws();
	if (right != NULL) rightr = right->getqvws();

	int size = leftr.size() + rightr.size();
	if (qvw->visited) size++;

	results.reserve(size);
	for (int i = 0; i < leftr.size(); i++) results.push_back(leftr[i]);
	if (qvw->visited) results.push_back(qvw);
	for (int i = 0; i < rightr.size(); i++) results.push_back(rightr[i]);

	return results;
}

vector<qvalweb*> qvaltree::getallqvws() 
{
	vector<qvalweb*> results(0);
	vector<qvalweb*> leftr(0);
	vector<qvalweb*> rightr(0);

	if (left != NULL) leftr = left->getallqvws();
	if (right != NULL) rightr = right->getallqvws();

	int size = leftr.size() + rightr.size()+1;

	results.reserve(size);

	for (int i = 0; i < leftr.size(); i++) 
		results.push_back(leftr[i]);

	results.push_back(qvw);

	for (int i = 0; i < rightr.size(); i++) 
		results.push_back(rightr[i]);

	return results;
}

