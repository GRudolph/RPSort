#ifndef __ACTIONLIST_H__
#define __ACTIONLIST_H__

#include "Action.h"

// ActionList
//
// ActionList is the object which contains a list of pointers to actions.  
// This is used by the Agent, qvalweb and state classes.  It may be ideal to 
// implement this as a Singleton.

class ActionList
{
    private:
        int numberActions;
        vector< Action* > actionList;
        
    public:
        ActionList();
        ~ActionList();
        
        void addAction(Action*);
        int getNumberActions();
        Action* getAction(int);
        int getRandomAction(state&);
        int getRandomAction();
};

#endif
