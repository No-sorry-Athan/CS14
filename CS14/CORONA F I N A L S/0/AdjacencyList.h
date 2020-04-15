#ifndef __ADJACENCYLIST_H__
#define __ADJACENCYLIST_H__

#include "Graph.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include <climits>

using namespace std;

class Vertex {
public:
    Vertex() :a(0), dist(INT_MAX), prev(0), color("WHITE") {};
    Vertex(int a) : a(a), dist(INT_MAX), prev(0), color("WHITE") {};
    vector<Vertex*> sink;
    int dist;
    int a;
    Vertex* prev;
    string color;
};

class AdjacencyList : public Graph {
    private:
        vector<Vertex> vertexes;
    public:
        AdjacencyList(string filename);

        bool empty() const;

        int vertices() const;
        int edges() const;
        int distance(int i) const;
        string path(int i) const;
        void bfs(int);
        void dfs(int);
        void display() const;

        int findIndex(int);

        void visit(int);
};

#endif // __ADJACENCYLIST_H__

