#ifndef USEFUL_H

#define USEFUL_H

#ifndef MY_USEFUL_LIBS
#include "usefullibs.h"
#endif

int atoi(char *a);
string itoa(int i);
int atoi(string a);
string trim(string s);
vector<string> tokenizer(string s);
string tolower(string s);
string round(double v, int s);
vector< vector<bool> > buildpmask(string filename);
void savepmask(vector< vector<bool> > pmask, string filename);

#endif
