#include "ActionList.h"
#include "userdefined.h"

// Constructor - numberActions is set to -1.  This ensures that NOOP is ignored
// in the action count.  If this is initialized to zero, there will require 
// a lot of change in several other components.

ActionList::ActionList() 
{	
	numberActions = -1;
	
	return;
}

// Destructor - All the action pointers must be deleted before this ActionList
// is deleted.

ActionList::~ActionList()
{
    // There needs to be some cleanup.  All the actions in the actionList
    // need to be deleted.
    
    Action* action;
    
    while(!actionList.empty())			// Keep deleting until empty!
    {
        action = actionList.back();		// get the last item pointer
        actionList.pop_back();			// and remove it from the list
        delete action;					// delete the item
    }
    
    return;
}      
    
// addAction - add an action to the list    
    
void ActionList::addAction(Action* action)
{
    actionList.push_back(action);
    numberActions++;
}
    
// getNumberAction - get the number of actions in the list    
    
int ActionList::getNumberActions()
{
    return numberActions;
}   

// get Action - return an pointer to the Action at index actionNumber

Action* ActionList::getAction(int actionNumber)
{
    return actionList[actionNumber];
}

// getRandomAction - return a random action from this list.  Ensure that this
// action can be performed on the currentState.

int ActionList::getRandomAction(state& curstate)
{
    int actionNumber;
    
//    do
//    {
        actionNumber = abs(rand()) % getNumberActions();
//    }
//    while(getAction(actionNumber)->canAct(curstate));
    
    return actionNumber;
}

// getRandomAction - return a random action without considering if it may be
// performed on the current state.

int ActionList::getRandomAction()
{
    return abs(rand()) % getNumberActions();
}
