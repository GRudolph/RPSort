#include "Action.h"

Action::Action()
{
    actionFunction = NULL;
    canActFunction = NULL;
    rewardFunction = NULL;

    return;
}

Action::~Action()
{
    return;
}

// set*Function allows a callback function for the act, canAct and Reward
// functions for this Action to be set.

void Action::setActionFunction (bool (*function) (state&))
{
    actionFunction = function;
    return;
}

void Action::setCanActFunction (bool (*function) (state&))
{
    canActFunction = function;
    return;
}

void Action::setRewardFunction (int (*function) (state&))
{
	rewardFunction = function;
	return;
}

// act modifies the currentState based on the function provided by the user.

bool Action::act (state &currentState)
{
    return actionFunction(currentState);
}

// canAct determines if this action can be performed on the current state.

bool Action::canAct (state &currentState)
{
    return canActFunction(currentState);
}

// reward determines the amount to reward or punish the Agent for this action.

int Action::reward (state &currentState)
{
	return rewardFunction(currentState);
}

// set / get Description provides a description of the action.  This is used
// when generating the policy report.

void Action::setDescription(string description)
{
    this->description = description;
    return;
}

string Action::getDescription()
{
    return description;
}

// Action factory implementation.
//
// This function takes as parameters the description of the action, and the
// functions for the action (can act, reward and act).  It returns a pointer
// to an Action object, which can be added to the Agent.

Action* createAction(bool (*actionFunc) (state&),
                     bool (*canActFunc) (state&), 
                     int (*rewardFunc) (state&),
                     string description)
{
    Action* action = new Action();
    action->setDescription(description);
    action->setActionFunction(actionFunc);
    action->setCanActFunction(canActFunc);
    action->setRewardFunction(rewardFunc);

    return action;
}                             

