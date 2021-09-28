#ifndef __ACTION_H__
#define __ACTION_H__

#include "state.h"

// Action
//
// The action class stores a user-defined action.  The Agent is able to call
// the user defined functions through this class.

class Action
{
	private:
		string description;
		bool (*actionFunction) (state&);
		bool (*canActFunction) (state&);
		int (*rewardFunction) (state&);
	
	public:
		Action();
		~Action();
		
		void setDescription(string);
		string getDescription();
		
		void setActionFunction (bool (*function) (state&));
		void setCanActFunction (bool (*function) (state&));
		void setRewardFunction (int (*function) (state&));
		
		bool act (state&);
		bool canAct (state&);
		int reward (state&);
};


// Factory for creating actions from desired functions.  User should utilize 
// this to create Actions for the agent.

Action* createAction( 
                     bool (*actionFunc) (state&),
                     bool (*canActFunc) (state&), 
                     int (*rewardFunc) (state&),
                     string description
                     );


#endif
