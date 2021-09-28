#ifndef USEFUL_H
#include "usefulfunc.h"
#endif

int atoi(char *a) {
	int n = strlen(a);
	int i = 0;
	bool negative = false;
	int j = 0;
	if (a[0] == '-') {
		negative = true;
		j++;
	} else	if (a[0] < '0' || a[0] > '9') return -1;

	for ( ; j < n; j++) i = i * 10 + (int)(a[j]) - (int)('0');

	if (negative) i *= -1;
	
	return i;
}

int atoi(string a) {
  int n = a.size();
  int i = 0;
  if (a[0] < '0' || a[0] > '9') return -1;

  for (int j = 0; j < n; j++) {
    i = i * 10 + (int)(a[j]) - (int)('0');
  }

  return i;
}

string itoa(int i) {
	if (i == 0) {
		return "0";
	}
	string temp = "";
	if (i < 0) {
		temp = "-";
		i = -i;
	}
	int j = i;
	while (j > 0) {
		int t = j % 10;
		temp = temp + (char)(t + (int)'0');
		j -= t;
		j /= 10;
	}

	string temp2 = "";
	for (int k = temp.size()-1; k >= 0; k--) temp2 += temp[k];

	return temp2;
}

string trim(string s) {
	int startstring = 0;
	while (startstring < s.size() && (s[startstring] < '!' || s[startstring] > '~')) startstring++;

	int endstring = s.size()-1;
	while (endstring >= startstring && (s[endstring] < '!' || s[endstring] > '~')) endstring--;

	string result = "";
	for (int i = startstring; i <= endstring; i++) result += s[i];

	return result;
}

string round(double v, int s) {
	int i = (int)v;
	double f = v - (double)i;
	double size = pow(10.0,s);

	f *= size;
	
	int ff = (int)f;
	string result = itoa(i) + "." + itoa(ff);

	return result;
}

vector<string> tokenizer(string s) {
	vector<string> result(0);

	string temp = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ') {
			result.push_back(temp);
			temp = "";
		} else temp += s[i];
	}
	if (temp.size() > 0) result.push_back(temp);

	return result;
}

string tolower(string s) {
	int diff = 'a' - 'A';
	string temp = "";
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			char newchar = s[i] + diff;
			temp = temp + newchar;
		} else temp += s[i];
	}
	
	return temp;
}

vector< vector<bool> > buildpmask(string filename) {
	ifstream infile(filename.c_str());
	char buffer[10000];

	infile.getline(buffer, 10000);
	string temp(buffer);
	int kcount = atoi(temp.c_str());

	infile.getline(buffer, 10000);
	temp = string(buffer);
	int excount = atoi(temp.c_str());

	vector< vector<bool> > pmask(0);
	pmask.reserve(kcount);

	for (int i = 0; i < kcount; i++) {
		vector<bool> pmask2(0);
		pmask2.reserve(excount);
		for (int j = 0; j < excount; j++) {
			infile.getline(buffer, 10000);
			temp = string(buffer);
			int val = atoi(temp.c_str());
			if (val == 0) {
				pmask2.push_back(false);
			} else pmask2.push_back(true);
		}
		pmask.push_back(pmask2);
	}

	infile.close();

	return pmask;
}

void savepmask(vector< vector<bool> > pmask, string filename) {
	ofstream ofile(filename.c_str());

	ofile << pmask.size() << endl << pmask[0].size() << endl;
	for (int i = 0; i < pmask.size(); i++) {
		for (int j = 0; j < pmask[i].size(); j++) {
			if (pmask[i][j]) {
				ofile << "1" << endl;
			} else ofile << "0" << endl;
		}
	}

	ofile.close();
}

// !strcasecmp(tempv[0].c_str(), "polynomial")
