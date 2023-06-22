#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    string sequence;
    int vertex;
    int color; // 0: branco, 1: cinza, 2: preto.
    vector<Node*> conectedNodes; // para quais vértices este atual leva
    int listSize;
};

class Digraph{
    protected:
        int V; // número de vértices
        int E; // número de arestas
        string StringDigraph; // representação em string
        vector<Node*> nodes;

    public:
        Digraph(); // cria um digrafo com V vértices sem arestas
        ~Digraph();
        string getStringDigraph(); // recebe a representação em string
        int getV();
        int getE();
        void readDigraph(); // lê o arquivo de entrada
        void teste(); // printa cada um dos vértices e os vértices para qual eles levam
        void removeCycle(); // remove os ciclos
        void Cycle(); // verifica há um ciclo
        void dfsR(int v, bool* marked, bool* onStack, queue<int>* fila); 
        vector<Node*> fixConnectedNodes(vector<Node*> auxVec, int i);
};