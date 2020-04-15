#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(string str) {
	ifstream ifs;
	ifs.open(str);
	if (!ifs.is_open()){
		cout << "Error opening " << str << endl;
		return;
	}

	int numRel, rel1, rel2;
	ifs >> numRel;
	v = vector<vector<int>>(numRel, vector<int>(numRel, 0));
	_distances = vector<int>(numRel, INT_MAX);
	_previous = vector<int>(numRel, -1);

	while (ifs >> rel1 >> rel2) {
		v.at(rel1).at(rel2) = 1;
	}
}

// Runtime: O(n^2) where n is number of vertices
// Space complexity: O(n) where n is number of vertices
void AdjacencyMatrix::bfs(int s) {
	queue<int> q; // O(1)
	vector<string> color = vector<string>(vertices(), "WHITE"); // O(n) where n is number of vertices
	_distances = vector<int>(vertices(), INT_MAX); // O(n)
	_previous = vector<int>(vertices(), -1); // O(n)

	color.at(s) = "GREY"; // O(1)
	_distances.at(s) = 0; // O(1)
	_previous.at(s) = -1; // O(1)
	q.push(s); // O(1)

	while (!q.empty()) { // O(n) number of vertices
		int temp = q.front(); // O(1)
		q.pop(); // O(1)
		for (unsigned i = 0; i < v.at(temp).size(); i++) { //O(n) n is number of vertices
			if (color.at(i) == "WHITE" && v.at(temp).at(i) == 1) { // O(1)
				_distances.at(i) = _distances.at(temp) + 1; // O(1)
				_previous.at(i) = temp; // O(1)
				color.at(i) = "GREY"; // O(1)
				q.push(i); // O(1)
			}
		}
		color.at(temp) = "BLACK"; // O (1)
	}
}


// Runtime: O(n^2) where n is number of vertices
// Space complexity: O(n) where n is number of vertices
void AdjacencyMatrix::dfs(int s) {
	vector<string> color = vector<string>(vertices(), "WHITE"); // O(n) where n is number of vertices
	_distances = vector<int>(vertices(), INT_MAX); // O(n)
	_previous = vector<int>(vertices(), -1); // O(n)

	color.at(s) = "GREY"; // O(1)
	_distances.at(s) = 0; // O(1)
	_previous.at(s) = -1; // O(1)
	visit(color, s); // O(n^2)
}

void AdjacencyMatrix::visit(vector<string>& color, int c) {
	color.at(c) = "GREY"; // O(1)
	for (int i = 0; i < v.at(c).size(); i++) { // O(n) 
		if (color.at(i) == "WHITE" && v.at(c).at(i) == 1) {// O(1)
			_distances.at(i) = _distances.at(c) + 1; // O(1)
			_previous.at(i) = c; // O(1)
			color.at(i) = "GREY"; // O(1)
			visit(color, i); // O(n)
		}
	}
	color.at(c) = "BLACK"; // O(1)
}

int AdjacencyMatrix::vertices() const {
	if (empty())
		return 0;
	return v.size();
}

int AdjacencyMatrix::edges() const {
	if (empty())
		return 0;
	int counter = 0;
	for (unsigned i = 0; i < v.size(); i++) {
		for (unsigned j = 0; j < v.size(); j++) {
			if (v.at(i).at(j) != 0) {
				counter++;
			}
		}
	}
	return counter;
}

int AdjacencyMatrix::distance(int i) const {
	return _distances.at(i);
}

string AdjacencyMatrix::path(int i) const {
	stack<int> backtrack;
	int temp = i;
	while (temp != -1) {
		backtrack.push(temp);
		temp = _previous.at(temp);
	}
	string s = "{";
	while (!backtrack.empty()) {
		int val = backtrack.top();
		backtrack.pop();
		s += to_string(val);
		if (!backtrack.empty())
			s += "->";
	}
	s += "}";
	return s;
}

void AdjacencyMatrix::display() const {

}


bool AdjacencyMatrix::empty() const {
	return v.size() == 0;
}
