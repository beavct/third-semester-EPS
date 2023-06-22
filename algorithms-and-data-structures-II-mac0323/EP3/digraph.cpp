#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include "digraph.h"
#define MAX 256

using namespace std;

Digraph:: Digraph(){
    this->V =0;
    this->E = 0;
}

Digraph:: ~Digraph(){

}

int Digraph:: getV(){
    return this->V;
}

int Digraph:: getE(){
    return this->E;
}

string Digraph:: getStringDigraph(){
    return this->StringDigraph;
}

void Digraph:: readDigraph(){
    fstream File;
    char filename[MAX];
    int min;

    cout << "Digite o nome do arquivo de entrada: ";
    cin >> filename;

    cout << "Indique o valor de k: ";
    cin >> min;

    File.open(filename, ios::in);

    int quantFrag;
    File >> quantFrag;

    for(int q=0; q<quantFrag; q++){
        Node* novo = new Node();

        File >> novo->sequence;
        novo->listSize = 0;
        novo->vertex = this->V;

        this->nodes.push_back(novo);
        this->V++;

        for(int i=0; i<V-1; i++){

            int j=0, k=0;
            int save;
            bool connection = false;

            // evita que dois vértices que possuem fragmentos iguais e formem um ciclo
            if(novo->sequence == nodes[i]->sequence)
                continue;
            
            // verifica se o nó que já está no grafo leva ao novo nó
            while(j < int(size(nodes[i]->sequence)) && nodes[i]->sequence[j] != novo->sequence[k]){
                j++;
            }
            save = j;

            while(j < int(size(nodes[i]->sequence)) && k < int(size(novo->sequence))){
                if(novo->sequence[k] == nodes[i]->sequence[j]){
                    k++;
                    j++;
                    connection = true;
                }
                else{
                    connection = false;
                    k=0;
                    save++;
                    j = save;
                }

            }

            if(k >= min && connection == true && j == int(size(nodes[i]->sequence))){
                nodes[i]->conectedNodes.push_back(novo);
                nodes[i]->listSize++;
                this->E++;
            }
            j=k=0;
            connection=false;

            // verifica se o novo nó leva à algum outro vértice que já está no grafo
            while(k < int(size(novo->sequence)) && nodes[i]->sequence[j] != novo->sequence[k]){
                k++;
            }
            save = k;

            while(k < int(size(novo->sequence)) && j < int(size(nodes[i]->sequence))){
                if(novo->sequence[k] == nodes[i]->sequence[j]){
                    k++;
                    j++;
                    connection = true;
                }
                else{
                    connection = false;
                    j=0;
                    save++;
                    k = save;
                }
            }

            if(j>=min && connection == true && k == int(size(novo->sequence))){
                novo->conectedNodes.push_back(nodes[i]);
                novo->listSize++;
                this->E++;
            }
            
        }

    }

    File.close();
}

void Digraph:: teste(){
    for(int i=0; i<int(this->nodes.size()); i++){
        cout << "seq orig " << nodes[i]->sequence << " " << nodes[i]->vertex <<  endl;

        for(int j=0; j<int(nodes[i]->listSize); j++){
            cout << nodes[i]->conectedNodes[j]->sequence << " " << nodes[i]->conectedNodes[j]->vertex << endl;
        }
        cout << "--------------------" << endl;

    }
}

void Digraph:: Cycle(){
    bool* onStack = new bool[this->V];
    bool* marked = new bool[this->V];
    queue<int>* q = new queue<int>(); 
    
    for(int i=0; i<this->V; i++){
        onStack[i] = false;
        marked[i] = false;
    }

    for(int v=0; v<this->V; v++){
        if(!marked[v]){
            dfsR(v, marked, onStack, q);
            //marked[v] = true;
            //cout << v << endl << endl;
        }
    }

    delete(marked);
    delete(onStack);
    delete(q);
}

vector<Node*> Digraph:: fixConnectedNodes(vector<Node*> auxVec, int i){
    for(int j=i; j<int(auxVec.size()); j++)
        auxVec[j] = auxVec[j+1];

    return auxVec;
}

void Digraph:: dfsR(int v, bool* marked, bool* onStack, queue<int>* fila){
    onStack[v] = true;
    marked[v] = true;
    vector<Node*> auxVec = this->nodes[v]->conectedNodes;
    int auxCount = this->nodes[v]->listSize; 

    fila->push(v);

    int save = this->nodes[v]->listSize;

    for(int w=0; w<this->nodes[v]->listSize; w++){
        //cout << v << endl << endl;
        //cout << "pai " << v << " " << this->nodes[v]->listSize << endl;
        //cout << "filho " << this->nodes[v]->conectedNodes[w]->vertex << endl;
        //cout << "topo " << fila->front() << endl;
        
        if(!marked[this->nodes[v]->conectedNodes[w]->vertex]){
            dfsR(this->nodes[v]->conectedNodes[w]->vertex, marked, onStack, fila);
        }

        else if(onStack[w] || fila->front() == this->nodes[v]->conectedNodes[w]->vertex){
            //cout << "--removemos " << this->nodes[v]->vertex << " -> " << this->nodes[v]->conectedNodes[w]->vertex << endl;
            for(int k=0; k<auxCount; k++){
                if(auxVec[k]->vertex == this->nodes[v]->conectedNodes[w]->vertex){
                    auxVec = fixConnectedNodes(auxVec, k);
                    break;
                }
            }

            auxCount--;
            //fila->pop();
            
        }



        //cout << "------------" << endl << endl;


    
    }

    onStack[v] = false;

    this->nodes[v]->conectedNodes = auxVec;
    this->nodes[v]->listSize = auxCount;

    //marked[v] = false;

    fila->pop();

}


