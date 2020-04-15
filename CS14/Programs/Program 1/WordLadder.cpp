#include "WordLadder.h"

WordLadder::WordLadder(const string& file) {
	ifstream fIn;
	fIn.open(file);
	if (!fIn.is_open()) {
		cout << "Error opening " << file << endl;
		return;
	}

	string word;
	while (fIn >> word) {
		if (word.length() != 5) {
			cout << "Word aint 5 characters idiot" << endl;
			return;
		}

		dict.push_back(word);
		if (fIn.fail())
			break;
	}
	fIn.close();

}

void WordLadder::outputLadder(const string& start, const string& end, const string& outputFile) {
	ofstream fOn;
	fOn.open(outputFile);
	if (!fOn.is_open()) {
		cout << "Error opening " << outputFile << endl;
		return;
	}
	stack<string> stk;
	queue<stack<string>> que;

	bool foundStart = false, foundEnd = false;

	list<string>::iterator iterate;
	for (iterate = dict.begin(); iterate != dict.end(); iterate++) {
		if (*iterate == start)
			foundStart = true;	
		if (*iterate == end)
			foundEnd = true;
	}

	if (!foundEnd || !foundStart) {
		cout << "Either the ending word or starting word were not found" << endl;
		return;
	}

	if (start == end) {
		fOn << start;
		return;
	}
	// stack with just first word
	stk.push(start);
	// enque stack onto stack of stacks
	que.push(stk);
	// remove word because we "used it up"
	dict.remove(start);
	// while que is not empty
	while (!que.empty()) {
		// get word on top of front stack
		string currentWord = que.front().top();
		
		for (iterate = dict.begin(); iterate != dict.end(); ++iterate) {
			string iterateWrd = *iterate;
			int amtSame = 0;
			for (int i = 0; i < 5; i++) {
				if (currentWord[i] == iterateWrd[i])
					amtSame++;
			}
			// check if word is off by one letter from top word
			if (amtSame == 4) {
				//create stack that is copy of front stack
				//stack<string> cpy;
				if (iterateWrd == end) {
					que.front().push(end);
					// print que (add to file / print by cout for error checking)
					stack<string> slack = que.front();
					vector<string> cpy;
					while (!slack.empty()) {
						cpy.push_back(slack.top());
						slack.pop();
					}
					for (int i = cpy.size() - 1; i >= 0; i--) {
						if (i == 0) {
							fOn << cpy.at(i);
							//cout << cpy.at(i);
							break;
						}
						fOn << cpy.at(i) << " ";
						//cout << cpy.at(i) << " ";
					}
					//cout << endl;
					fOn << endl;
					fOn.close();
					return;
				}
				stk = que.front();
				// push one off word found
				stk.push(iterateWrd);
				// push onto the que
				que.push(stk);

				// not final word, remove word from dictionary because "used up"
				// also i dont really know why its iterate = dict.erase
				// sorta just saw it on stackoverflow when i searched up why i kept getting an error trying to just do iterate--
				iterate = dict.erase(iterate);
				// moving iterator back by one, so it properly checks word after removing a used one
				iterate--;
			}
		}
		// deque this front stack
		que.pop();
	}
	// queue is empty and did not find a word ladder 
	fOn << "No Word Ladder Found." << endl;
	fOn.close();
}