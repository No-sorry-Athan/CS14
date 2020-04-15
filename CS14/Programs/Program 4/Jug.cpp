#include "Jug.h"



Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {};

Jug::~Jug() {

}

int Jug::solve(string& sol) {
    if (Ca < 1 || Cb < 1 || Cb > 1000 || Ca > Cb || N < 0 || N > Cb || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0)
    {
        sol = "";

        return -1;
    }

    Vertex empty(0, 0);

    vertices.push_back(empty);
    vertices.at(0).dist = 0;
    vertices.at(0).prev = -1;
    process.push(0);
    buildGraph();

    string success;

    success = dijkstra();
    if (success.empty())
    {
        return 0;
    }
    while (!traverse.empty())
    {
        sol += (traverse.top() + '\n');
        traverse.pop();
    }
    sol += success;

    return 1;
}

void Jug::buildGraph() {
    while (!process.empty()) {
        bool found = false;
        uint current = process.top();
        process.pop();
        for (uint i = 0; i < visited.size(); i++)
        {
            if (current == visited.at(i))
            {
                found = true;
                break;
            }
        }
        if (!found){
            visited.push_back(current);
            process.push(fillA(current));
            process.push(fillB(current));
            process.push(emptyA(current));
            process.push(emptyB(current));
            process.push(pourAB(current));
            process.push(pourBA(current));
        }
    }
}

string Jug::dijkstra() {
    for (uint i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).amntB == N)
            break;
        else if (i == vertices.size() - 1)
            return "";
    }
    list<pair<int, int>>::iterator nei;
    list<pair<int, string>>::iterator rel;
    for (uint i = 0; i < vertices.size(); i++) {
        nei = vertices.at(i).neighbors.begin();
        rel = vertices.at(i).relation.begin();
        while (nei != vertices.at(i).neighbors.end()) {
            Vertex temp = vertices.at(findIndex(Vertex(nei->first, nei->second)));
            while (rel != vertices.at(i).relation.end()) {
                int index = findIndex(Vertex(nei->first, nei->second));
                if (vertices.at(index) == vertices.at(rel->first)) {
                    if (vertices.at(i).dist + findCost(rel->second) < temp.dist) {
                        vertices.at(findIndex(temp)).dist = vertices.at(i).dist + findCost(rel->second);
                        vertices.at(findIndex(temp)).prev = i;
                    }
                }
                rel++;
            }

            nei++;
            rel = vertices.at(i).relation.begin();
        }
    }
    //for (uint i = 0; i < vertices.size(); i++) {
    /*    cout << vertices.at(i).amntA << " " << vertices.at(i).amntB << " " << vertices.at(i).prev << " " << vertices.at(i).dist << endl;
    }*/
    list<pair<int, int>>::iterator thing;
    thing = vertices.at(3).neighbors.begin();
    
    Vertex temp(0, N);
    int index = findIndex(temp);
     while (vertices.at(index).prev != -1) {
        list<pair<int, int>>::iterator nei = vertices.at(vertices.at(index).prev).neighbors.begin();
        list<pair<int, string>>::iterator rel = vertices.at(vertices.at(index).prev).relation.begin();
        while (nei != vertices.at(vertices.at(index).prev).neighbors.end()) {
            Vertex temppp(nei->first, nei->second);
            int bread = findIndex(temppp);
            if (bread == vertices.at(index).prev) {
                while (rel != vertices.at(vertices.at(index).prev).relation.end()) {
                    if (rel->first == index) {
                        traverse.push(rel->second);
                    }
                    rel++;
                }
            }
            nei++;
        }
        index = vertices.at(index).prev;
    }
    stringstream ss;
    int breadbowl = findIndex(temp);
    ss << vertices.at(breadbowl).dist;
    return "success " + ss.str();
}

uint Jug::fillA(uint curr) {
    Vertex cV = vertices.at(curr);
    Vertex nV(Ca, cV.amntB);
    if (!exists(nV)) {
        vertices.push_back(nV);
        int ind = findIndex(nV);
        vertices.at(curr).neighbors.push_back(std::pair<int, int>(nV.amntA, nV.amntB));
        vertices.at(curr).relation.push_back(std::pair<int, string>(ind, "fill A"));
        vertices.at(ind).neighbors.push_back(std::pair<int, int>(vertices.at(curr).amntA, vertices.at(curr).amntB));
    }
    else {
        //int ind = findIndex(nV);
        vertices.at(curr).neighbors.push_back(std::pair<int, int>(nV.amntA, nV.amntB));
        vertices.at(curr).relation.push_back(std::pair<int, string>(findIndex(nV), "fill A"));
        //vertices.at(ind).neighbors.push_back(std::pair<int, int>(vertices.at(curr).amntA, vertices.at(curr).amntB));
    }
    return findIndex(nV);
}

uint Jug::fillB(uint curr) {
    Vertex cV = vertices.at(curr);
    Vertex nV(cV.amntA, Cb);
    if (!exists(nV)) {
        vertices.push_back(nV); 
        int ind = findIndex(nV);
        vertices.at(curr).neighbors.push_back(std::pair<int, int>(nV.amntA, nV.amntB));
        vertices.at(curr).relation.push_back(std::pair<int, string>(ind, "fill B"));
        //vertices.at(ind).neighbors.push_back(std::pair<int, int>(vertices.at(curr).amntA, vertices.at(curr).amntB));
    }
    else {
        //int ind = findIndex(nV);
        vertices.at(curr).neighbors.push_back(std::pair<int, int>(nV.amntA, nV.amntB));
        vertices.at(curr).relation.push_back(std::pair<int, string>(findIndex(nV), "fill B"));
        //vertices.at(ind).neighbors.push_back(std::pair<int, int>(vertices.at(curr).amntA, vertices.at(curr).amntB));
    }
    return findIndex(nV);
}

uint Jug::pourAB(uint curr) {
    Vertex cV = vertices.at(curr);
    int neighborA = vertices.at(curr).amntA;
    int neighborB = vertices.at(curr).amntB;

    while (neighborA > 0 && neighborB < Cb)
    {
        neighborA--;
        neighborB++;
    }

    Vertex nV(neighborA, neighborB);
    if (!exists(nV)) {
        vertices.push_back(nV);
        int ind = findIndex(nV);
        vertices.at(curr).neighbors.push_back(std::pair<int, int>(nV.amntA, nV.amntB));
        vertices.at(curr).relation.push_back(std::pair<int, string>(ind, "pour A B"));
        //vertices.at(ind).neighbors.push_back(std::pair<int, int>(vertices.at(curr).amntA, vertices.at(curr).amntB));
    }
    else {
        //int ind = findIndex(nV);
        vertices.at(curr).neighbors.push_back(std::pair<int, int>(nV.amntA, nV.amntB));
        vertices.at(curr).relation.push_back(std::pair<int, string>(findIndex(nV), "pour A B"));
        //vertices.at(ind).neighbors.push_back(std::pair<int, int>(vertices.at(curr).amntA, vertices.at(curr).amntB));
    }
    return findIndex(nV);

}

uint Jug::pourBA(uint curr) {
    Vertex cV = vertices.at(curr);
    int neighborA = vertices.at(curr).amntA;
    int neighborB = vertices.at(curr).amntB;

    while (neighborA < Ca && neighborB > 0)
    {
        neighborA++;
        neighborB--;
    }

    Vertex nV(neighborA, neighborB);
    if (!exists(nV)) {
        vertices.push_back(nV);
        int ind = findIndex(nV);
        vertices.at(curr).neighbors.push_back(std::pair<int, int>(nV.amntA, nV.amntB));
        vertices.at(curr).relation.push_back(std::pair<int, string>(ind, "pour B A"));
        //vertices.at(ind).neighbors.push_back(std::pair<int, int>(vertices.at(curr).amntA, vertices.at(curr).amntB));
    }
    else {
        //int ind = findIndex(nV);
        vertices.at(curr).neighbors.push_back(std::pair<int, int>(nV.amntA, nV.amntB));
        vertices.at(curr).relation.push_back(std::pair<int, string>(findIndex(nV), "pour B A"));
        //vertices.at(ind).neighbors.push_back(std::pair<int, int>(vertices.at(curr).amntA, vertices.at(curr).amntB));
    }
    return findIndex(nV);
}

uint Jug::emptyA(uint curr) {
    Vertex cV = vertices.at(curr);
    Vertex nV(0, cV.amntB);
    if (!exists(nV)) {
        vertices.push_back(nV);
        int ind = findIndex(nV);
        vertices.at(curr).neighbors.push_back(std::pair<int, int>(nV.amntA, nV.amntB));
        vertices.at(curr).relation.push_back(std::pair<int, string>(ind, "empty A"));
        //vertices.at(ind).neighbors.push_back(std::pair<int, int>(vertices.at(curr).amntA, vertices.at(curr).amntB));
    }
    else {
        //int ind = findIndex(nV);
        vertices.at(curr).neighbors.push_back(std::pair<int, int>(nV.amntA, nV.amntB));
        vertices.at(curr).relation.push_back(std::pair<int, string>(findIndex(nV), "empty A"));
        //vertices.at(ind).neighbors.push_back(std::pair<int, int>(vertices.at(curr).amntA, vertices.at(curr).amntB));
    }
    return findIndex(nV);
}

uint Jug::emptyB(uint curr) {
    Vertex cV = vertices.at(curr);
    Vertex nV(cV.amntA, 0);
    if (!exists(nV)) {
        vertices.push_back(nV);
        int ind = findIndex(nV);
        vertices.at(curr).neighbors.push_back(std::pair<int, int>(nV.amntA, nV.amntB));
        vertices.at(curr).relation.push_back(std::pair<int, string>(ind, "empty B"));
        //vertices.at(ind).neighbors.push_back(std::pair<int, int>(vertices.at(curr).amntA, vertices.at(curr).amntB));
    }
    else {
        //int ind = findIndex(nV);
        vertices.at(curr).neighbors.push_back(std::pair<int, int>(nV.amntA, nV.amntB));
        vertices.at(curr).relation.push_back(std::pair<int, string>(findIndex(nV), "empty B"));
       //vertices.at(ind).neighbors.push_back(std::pair<int, int>(vertices.at(curr).amntA, vertices.at(curr).amntB));
    }
    return findIndex(nV);
}

bool Jug::exists(int a, int b) const {
    for (uint i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).amntA == a && vertices.at(i).amntB == b) 
            return true;
    }
    return false;
}

bool Jug::exists(Vertex curr) const {
    return exists(curr.amntA, curr.amntB);
}

int Jug::findIndex(Vertex curr) const {
    if (exists(curr))
        return findIndex(curr.amntA, curr.amntB);
    else
        return -1;
}

int Jug::findIndex(int a, int b) const{
    for (uint i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).amntA == a && vertices.at(i).amntB == b)
            return i;
    }
    return -1;
}

int Jug::findCost(const string& str) {
    if (str == "fill A")
    {
        return cfA;
    }
    else if (str == "fill B")
    {
        return cfB;
    }
    else if (str == "empty A")
    {
        return ceA;
    }
    else if (str == "empty B")
    {
        return ceB;
    }
    else if (str == "pour A B")
    {
        return cpAB;
    }
    else
    {
        return cpBA;
    }
}