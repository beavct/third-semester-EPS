#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
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

    cout << "Digite o nome do arquivo de entrada: ";
    cin >> filename;

    File.open(filename, ios::in);

    int quantFrag;
    File >> quantFrag;

    for(int q=0; q<quantFrag; q++){
        Node* novo = new Node();

        File >> novo->sequence;
        novo->listSize = 0;

        this->nodes.push_back(novo);
        this->V++;

        for(int i=0; i<V-1; i++){
            int j=0, k=0;
            int save;
            bool connection = false;
            
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
                    //continue;
                }

            }

            if(connection == true && j == int(size(nodes[i]->sequence))){
                //novo->conectedNodes.push_back(nodes[i]);
                //novo->listSize++;
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
                    //break;
                }
            }

            if(connection == true && k == int(size(novo->sequence))){
                novo->conectedNodes.push_back(nodes[i]);
                novo->listSize++;
                //nodes[i]->conectedNodes.push_back(novo);
                //nodes[i]->listSize++;
                this->E++;
            }
            
        }

    }

    File.close();
}

void Digraph:: teste(){
    for(int i=0; i<int(this->nodes.size()); i++){
        cout << "seq orig " << nodes[i]->sequence << " " << i <<  endl;

        for(int j=0; j<int(nodes[i]->conectedNodes.size()); j++){
            cout << nodes[i]->conectedNodes[j]->sequence << " " << j << endl;
        }
        cout << "--------------------" << endl;

    }
}

void Digraph:: removeCycle(){
    
}

bool Digraph:: hasCycle(){
    bool* onStack = new bool[this->V]; // guarda os vértices que as chamadas recurssivas ainda não chegaram
    bool* marked = new bool[this->V];
    
    for(int i=0; i<this->V; i++){
        onStack[i] = false;
        marked[i] = false;
    }

    for(int v=0; v<this->V; v++){
        if(!marked[v]){
            dfsR(v, this->nodes[v], marked, onStack);
        }
    }


    delete(marked);
    return false;
}

void Digraph:: dfsR(int v, Node* V, bool* marked, bool* onStack){
    onStack[v] = true;
    marked[v] = true;
    
    //cout << this->nodes[v]->sequence <<" entrou em dfsR " << this->nodes[v]->listSize << endl;


    for(int w=0; w<this->nodes[v]->listSize; w++){
        //cout << this->nodes[v]->listSize << endl;
        //cout << this->nodes[v]->sequence << "->" << this->nodes[v]->conectedNodes[w]->sequence << endl;
        if(!marked[w]){
            //cout << "chamada recurssiva" << endl;
            dfsR(w, this->nodes[v]->conectedNodes[w], marked, onStack);
        }
        //else if(this->nodes[v]->conectedNodes[w] != V && onStack[w]){
        else if(onStack[w]){
            vector<Node*> aux;
            //cout << "tiramos " << this->nodes[v]->sequence << endl;

            cout << endl << endl;

            this->teste();

            cout << endl << endl;

            int j=0;
            for(int i=0; i< this->nodes[v]->listSize && this->nodes[v]->conectedNodes[i] != nullptr; i++){
                //cout << (this->nodes[w]->conectedNodes[this->nodes[w]->listSize] == nullptr) << endl;

                if(i != w)
                    aux[j++] = this->nodes[v]->conectedNodes[i];

            }

            this->nodes[v]->conectedNodes.clear();
            this->nodes[v]->conectedNodes = aux;

            this->nodes[v]->listSize--;    
            //onStack[w] = false;
        }

    }


}


