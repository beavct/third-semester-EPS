#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <fstream>

#pragma once

using namespace std;

struct Vertex{
    char letter;
    int listN;
    int vertex;
    bool lambdaT;
    int op;
    vector<Vertex*> vList; 
};

class Automata {
    private:
        int V; 
        string automataS;
        vector<Vertex*> adjList;
        string *words;
        int wordsN;

    public:
        Automata();
        ~Automata();
        bool verifyWord(string word);
        int defineOp(int i);
        bool defineLambdaT(int i);
        void dfsR(int i, bool* marked);
        void readInput(string filename);
        void makeConnections();
        void createVertex();
        void addEdge(int i, int j);
        void verifyAllWords();
};