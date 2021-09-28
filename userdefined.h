
#ifndef __USERDEFINED_H__
#define __USERDEFINED_H__

#include "state.h"
#include "usefullibs.h"
#include "Action.h"

bool issorted2(vector<int> &list);

bool NOOPaction(state &curstate);
bool NOOPcanAct(state &curstate);
int NOOPreward(state &curstate);

bool INCIaction(state &curstate); 
bool INCIcanAct(state &curstate);
int INCIreward(state &curstate);

bool INCJaction(state &curstate);
bool INCJcanAct(state &curstate); 
int INCJreward(state &curstate);

bool INCKaction(state &curstate);
bool INCKcanAct(state &curstate); 
int INCKreward(state &curstate);

bool SETIZEROaction(state &curstate); 
bool SETIZEROcanAct(state &curstate);
int SETIZEROreward(state &curstate);

bool SETJZEROaction(state &curstate);
bool SETJZEROcanAct(state &curstate); 
int SETJZEROreward(state &curstate);

bool SETKZEROaction(state &curstate);
bool SETKZEROcanAct(state &curstate); 
int SETKZEROreward(state &curstate);

bool SWAPaction(state &curstate);
bool SWAPcanAct(state &curstate);
int SWAPreward(state &curstate);


bool TERMINATEaction(state &curstate); 
bool TERMINATEcanAct(state &curstate);
int TERMINATEreward(state &curstate);


#endif
