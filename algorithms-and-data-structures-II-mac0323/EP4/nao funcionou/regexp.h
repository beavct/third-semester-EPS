#include <string>

#pragma once

using namespace std;

struct vertex
{
    char symbol;
    int index;
    vertex **edges;
    int edgesN;
    bool lambdaT;
    int op; // 0 - complemento, 1 - intervalo, 2 - conjunto, -1 - nenhuma das anteriores
};


class Automata{
    protected:
        string automataS;
        int V;
        vertex* symbols;
        int wordsN;
        string* words;

    public:
        Automata();
        ~Automata();
        void readInput(string filename);
        void makeConnections();
        void addEdge(int i, int j);
        void verifyAllWords();
        bool verifyWord(string word);
        void teste();
        void dfsR(int i, bool* marked);
        void createVertex();
        int defineOp(int i);
        bool defineLambdaT(int i);
};