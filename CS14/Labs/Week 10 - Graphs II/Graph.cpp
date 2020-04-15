#include "Graph.h"

Graph::Graph() {
	// wtf
}

Graph::Graph(ifstream& ifs) {
	int numVertices = 0;
	int numRelations = 0;
	ifs >> numVertices;
	ifs >> numRelations;

	for (int i = 0; i < numVertices; i++) {
		string word;
		ifs >> word;

		Vertex temp;
		temp.label = word;
		vertices.push_back(temp);
	}

	for (int i = 0; i < numRelations; i++) {
		string v1;
		string v2;
		int weight;
		ifs >> v1;
		ifs >> v2;
		ifs >> weight;
		int ind1 = findIndex(v1);
		int ind2 = findIndex(v2);

		vertices.at(ind1).neighbors.push_back(std::pair<int, int>(ind2, weight));

	}

}

int Graph::findIndex(const string& str) const {
	for (unsigned i = 0; i < vertices.size(); i++) {
		if (vertices.at(i).label == str)
			return i;
	}
	return -1;
}

Graph::~Graph() {
	while (!vertices.empty()) {
		vertices.pop_back();
	}
}

void Graph::output_graph(const string& str) {
	ofstream ofs;
	ofs.open(str);
	if (!ofs.is_open()) {
		cout << "Error opening " << str << endl;
		return;
	}

	ofs << "diagraph G {" << endl;
	for (unsigned i = 0; i < vertices.size(); i++) {
		if (vertices.at(i).distance != INT_MAX) {
			ofs << vertices.at(i).label << "[label = \"" << vertices.at(i).label << ", " << vertices.at(i).distance << "\"]" << endl;
		}
		if (!vertices.at(i).neighbors.empty()) {
			list<pair<int, int> > ::iterator it = vertices.at(i).neighbors.begin();
			while (it != vertices.at(i).neighbors.end()) {
				if (vertices.at(i).distance != INT_MAX) {
					ofs << vertices.at(i).label << " -> " << vertices.at(it->first).label << endl;
				}
				it++;
			}
		}
	}
	ofs << "}";
	ofs.close();
	string jpgFilename = str.substr(0, str.size() - 4) + ".jpg";
	string command = "dot -Tpng " + str + " -o " + jpgFilename;
	system(command.c_str());
	return;

}

void Graph::bfs() {
	queue<Vertex> q;
	for (unsigned i = 0; i < vertices.size(); i++) {
		vertices.at(i).color = "WHITE";
		vertices.at(i).distance = INT_MAX;
		vertices.at(i).prev = nullptr;
	}

	vertices.at(0).color = "GRAY";
	vertices.at(0).distance = 0;
	q.push(vertices.at(0));

	Vertex currentVec;
	while (!q.empty()) {
		currentVec = q.front();
		q.pop();
		list<pair<int, int>>::iterator it = currentVec.neighbors.begin();
		int ind = findIndex(currentVec.label);
		while (it != currentVec.neighbors.end()) {
			if (vertices.at(it->first).color == "WHITE") {
				vertices.at(it->first).color = "GRAY";
				vertices.at(it->first).distance = currentVec.distance + it->second;
				vertices.at(it->first).prev = &vertices.at(ind);
				q.push(vertices.at(it->first));
			}
			//vertices.at(it->first).color = "BLACK";

			it++;
		}
	}
}

int Graph::distance(const string& str) const {
	int index = findIndex(str);
	if (index != -1)
	return vertices.at(index).distance;
	else {
		return -1;
	}
}

string Graph::previous(const string& str) const {
	int index = findIndex(str);
	Vertex temp = vertices.at(index);
	if (temp.prev != nullptr)
		return vertices.at(index).prev->label;
	else {
		return "";
	}
}