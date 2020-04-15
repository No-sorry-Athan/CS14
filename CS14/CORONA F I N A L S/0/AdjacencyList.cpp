#include "AdjacencyList.h"

AdjacencyList::AdjacencyList(string filname) {
	ifstream ifs;
	ifs.open(filname);
	
	if (!ifs.is_open()) {
		cout << "Error opening " << filname << endl;
		return;
	}

	int bigNum, rel1, rel2;
	ifs >> bigNum;
	for (unsigned i = 0; i < bigNum; i++) {
		vertexes.push_back(i);
	}

	while (ifs >> rel1 >> rel2) {
		vertexes.at(rel1).sink.push_back(&vertexes.at(rel2));
	}

}

bool AdjacencyList::empty() const {
	return vertexes.size() == 0;
}

int AdjacencyList::vertices() const {
	if (empty()) {
		return 0;
	}
	return vertexes.size();
}

int AdjacencyList::edges() const {
	if (empty())
		return 0;

	int counter = 0;
	for (int i = 0; i < vertexes.size(); i++) {
		Vertex temp = vertexes.at(i);
		for (unsigned j = 0; j < temp.sink.size(); j++) {
			counter++;
		}
	}
	return counter;
}

int AdjacencyList::distance(int i) const {
	return vertexes.at(i).dist;
}

std::string AdjacencyList::path(int i) const {
	stack<int> backtrack;
	Vertex temp = vertexes.at(i);
	while (temp.prev != nullptr) {
		backtrack.push(temp.a);
		temp = *temp.prev;
	}
	backtrack.push(temp.a);
	string s = "{";
	while (!backtrack.empty()) {
		int val = backtrack.top();
		s += to_string(val);
		backtrack.pop();
		if (!backtrack.empty())
			s += "->";
	}
	s += "}";
	return s;

}


// Runtime: O(n*m) where n is number of vertexes and m is size of sink (number of relationships)
// Space Complexity: O(n) where n is number of vertexes
void AdjacencyList::bfs(int s) {
	queue<Vertex> q; // O(1)
	for (unsigned i = 0; i < vertexes.size(); i++) {  // O(n) is number of vertexes
		vertexes.at(i).dist = INT_MAX; // O(1)
		vertexes.at(i).prev = 0; // O(1)
		vertexes.at(i).color = "WHITE"; // O(1)
	}
	vertexes.at(s).color = "GREY"; // O(1)
	vertexes.at(s).dist = 0; // O(1)
	q.push(vertexes.at(s)); // O(1)

	Vertex currVer; // O(1)
	while (!q.empty()) {  // O(n) number of vertexes
		currVer = q.front(); // O(1)
		q.pop(); // O(1)

		int currInd = findIndex(currVer.a); // O(n)
		for (unsigned i = 0; i < currVer.sink.size(); i++) { // O(m) where m is size of sink
			int index2 = findIndex(vertexes.at(currInd).sink.at(i)->a); // O(n)
			if (vertexes.at(index2).color == "WHITE") { // O(1)
				vertexes.at(index2).dist = vertexes.at(currInd).dist + 1; // O(1)
				vertexes.at(index2).prev = &vertexes.at(currInd); // O(1)
				vertexes.at(index2).color = "GREY"; // O(1)
				q.push(vertexes.at(index2)); // O(1)
			}
		}
		vertexes.at(currInd).color = "BLACK"; // O(1)
	}
}

int AdjacencyList::findIndex(int a) {
	for (unsigned i = 0; i < vertexes.size(); i++) {
		if (vertexes.at(i).a == a) {
			return i;
		}
	}
	return -1;
}

// Runtime: O(n*m) where n is number of vertices and m is size of sink (number of relationships)
// Space Complexity: O(n) where n is number of vertices
void AdjacencyList::dfs(int s) {
	for (unsigned i = 0; i < vertexes.size(); i++) {  // O(n) is number of vertexes
		vertexes.at(i).dist = INT_MAX; // O(1)
		vertexes.at(i).prev = 0; // O(1)
		vertexes.at(i).color = "WHITE"; // O(1)
	}
	vertexes.at(s).color = "GREY"; // O(1)
	vertexes.at(s).dist = 0; // O(1)

	visit(s); // O(n*m)
}

void AdjacencyList::visit(int c) {
	vertexes.at(c).color = "GREY"; // O(1)
	for (int i = 0; i < vertexes.at(c).sink.size(); i++) { // O(m)
		int ind = findIndex(vertexes.at(c).sink.at(i)->a); // O(n)
		if (vertexes.at(ind).color == "WHITE") { // O(1)
			vertexes.at(ind).color = "GREY";// O(1)
			vertexes.at(ind).prev = &vertexes.at(c);// O(1)
			vertexes.at(ind).dist = vertexes.at(c).dist + 1;// O(1)
			visit(ind); // O(n*m)
		}
	}
	vertexes.at(c).color = "BLACK";// O(1)
}

void AdjacencyList::display() const {
	for (int i = 0; i < vertexes.size(); i++) {
		cout << path(i) << endl;
	}
}