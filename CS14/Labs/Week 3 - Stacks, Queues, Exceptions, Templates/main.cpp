#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <time.h>

using namespace std;

template<typename T>
unsigned min_index(const vector<T>& vals, unsigned index) {
	auto minLoc = index;
	for (unsigned i = index; i < vals.size(); i++) {
		if (vals[minLoc] > vals[i])
			minLoc = i;
	}
	return minLoc;
}

template<typename T>
void selection_sort(vector<T> &vals) {
	for (unsigned i = 0; i < vals.size(); i++) {
		unsigned minLoc = min_index(vals, i);
		auto temp = vals[i];
		vals[i] = vals[minLoc];
		vals[minLoc] = temp;
	}
}

template<typename T>
T getElement(vector<T> vals, int index) {
	unsigned temp = (unsigned)index;
	if (temp < 0 || temp > vals.size()) throw out_of_range("out of range exception occured");

	return vals[temp];
}

vector<char> createVector() {
	int vecSize = rand() % 26;
	char c = 'a';
	vector<char> vals;
	for (int i = 0; i < vecSize; i++)
	{
		vals.push_back(c);
		c++;
	}
	return vals;
}

int main() {
	 
	srand(time(0));
	vector<char> vals = createVector();
	char curChar;
	int index;
	int numOfRuns = 10;
	while (--numOfRuns >= 0) {
		cout << "Enter a number: " << endl;
		try {
			cin >> index;
			curChar = getElement(vals, index);
			cout << "Element located at " << index << ": is " << curChar << endl;
		}
		catch (out_of_range&) {
			cout << "out of range exception occured" << endl;
		}
	}
	return 0;
}