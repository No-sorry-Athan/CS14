#ifndef  JUG_H
#define JUG_H

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <climits>
#include <sstream>

typedef unsigned int uint;
using namespace std;

class Vertex {
    friend class Jug;
public:
    Vertex(int amntA, int amntB) :amntA(amntA), amntB(amntB), dist(INT_MAX),color("WHITE"),prev(-1) {};
private:
    int amntA;
    int amntB;
    unsigned int dist;
    string color;
    int prev;
    
    list<pair<int, int>> neighbors;
    list < pair<int, string>> relation;

    bool operator==(Vertex& thing) {
        return ((thing.amntA == this->amntA) && (thing.amntB == this->amntB));
    }
 
};

class Jug {
public:
	Jug(int, int, int, int, int, int, int, int, int);
	~Jug();

    //solve is used to check input and find the solution if one exists
    //returns -1 if invalid inputs. solution set to empty string.
    //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    //returns 1 if solution is found and stores solution steps in solution string.
    int solve(string& solution);
private:
    int Ca;
    int Cb;
    int N;
    int cfA;
    int cfB;
    int ceA;
    int ceB;
    int cpAB;
    int cpBA;
    vector<Vertex> vertices;
    stack<uint> process;
    vector<uint> visited;
    stack<string> traverse;

    uint fillA(uint);
    uint fillB(uint);
    uint pourAB(uint);
    uint pourBA(uint);
    uint emptyA(uint);
    uint emptyB(uint);
    string dijkstra();
    void buildGraph();
    bool exists(Vertex) const;
    bool exists(int, int) const;
    int findIndex(Vertex) const;
    int findIndex(int, int) const;

    int findCost(const string&);

};
#endif // ! JUG_H