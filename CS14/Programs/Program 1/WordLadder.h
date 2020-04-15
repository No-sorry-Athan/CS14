#ifndef WORD_LADDER_H
#define WORD_LADDER_H

#include <string>
#include <list>
#include <queue>
#include <stack>
#include <fstream>
#include <iostream>

using namespace std;

class WordLadder {
private: 
	list<string> dict;
public:
	WordLadder(const string&);
	void outputLadder(const string&, const string&, const string&);
};
#endif // !WORD_LADDER
