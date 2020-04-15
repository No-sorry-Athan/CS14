#ifndef __ADJACENCYMATRIX_H__
#define __ADJACENCYMATRIX_H__

#include "Graph.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

class AdjacencyMatrix : public Graph {
    private:
        vector<vector<int>> v;
    public:
        AdjacencyMatrix(std::string filename);

        int vertices() const;
        int edges() const;
        int distance(int i) const;
        std::string path(int i) const;
        void bfs(int);
        void dfs(int);
        void display() const;
        bool empty() const;
        void visit(vector<string>&, int);


};

#endif // __ADJACENCYMATRIX_H__
