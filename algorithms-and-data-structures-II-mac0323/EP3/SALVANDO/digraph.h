#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <stack>

using namespace std;

struct Node
{
    string sequence;
    vector<Node*> conectedNodes; // para quais vértices este atual leva
    int listSize;
};


class Digraph{
    protected:
        int V; // número de vértices
        int E; // número de arestas
        string StringDigraph; // representação em string
        vector<Node*> nodes;
        vector<int> cycle;

    public:
        Digraph(); // cria um digrafo com V vértices sem arestas
        ~Digraph();
        int adj(int v); // vértices conectado à vo por arestas saindo de v
        string getStringDigraph(); // recebe a representação em string
        int getV();
        int getE();
        void readDigraph(); // lê o arquivo de entrada
        void teste(); // printa cada um dos vértices e os vértices para qual eles levam
        void removeCycle(); // remove os ciclos
        bool hasCycle(); // verifica há um ciclo
        void dfsR(int v, Node* V, bool* marked, bool* onStack); 
};