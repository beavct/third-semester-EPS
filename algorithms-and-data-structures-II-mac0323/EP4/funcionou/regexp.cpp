#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <ctype.h>
#include "regexp.h"

using namespace std;

// construtor
Automata:: Automata(){

}

// destrutor
Automata:: ~Automata(){

}

// faz a leitura do arquivo
void Automata:: readInput(string filename){
    fstream file;

    file.open(filename.c_str());
    // pegar a linha toda mesmo que tenha espaço vazio entre as letras
    getline(file, this->automataS);

    file >> this->wordsN;

    this->words = new string[this->wordsN];

    string auxS;
    for(int i=0; i<this->wordsN; i++){
        file >> auxS;
        this->words[i] = auxS;
    }

    file.close();
}

// cria os vértices do automoto, sem nenhuma aresta
void Automata:: createVertex(){
    this->V = 0;
    int auxI = (int)this->automataS.length();


    for(int i=0; i<auxI; i++){
        Vertex* aux = new Vertex();
        aux->listN = 0;
        aux->letter = this->automataS[i];
        aux->vertex = this->V;
        aux->op = defineOp(i);
        aux->lambdaT = defineLambdaT(i);

        this->adjList.push_back(aux);
        this->V++;
    }
    this->V = auxI;
}

// define se o caracter da expressão regular é um símbolo a ser consumido ou uma operação que possui transição lambda
bool Automata::defineLambdaT(int i){
    if(this->automataS[i] == '|' || this->automataS[i] == '(' || this->automataS[i] == ')' || this->automataS[i] == '[' || this->automataS[i] == ']' || this->automataS[i] == '+' || this->automataS[i] == '*' || this->automataS[i] == '\\'){
        if(i == 0) 
            return true;

        else if(this->automataS[i-1] != '\\') 
            return true;
    }

    return false;
}

// define se o caracter é alguma operação não básica ([^], [-], [])
int Automata::defineOp(int i){
    if(this->automataS[i-1] == '['){

        if(this->automataS[i] == '^')
            return 0; // complemento

        else if(this->automataS[i+1] == '-')
            return 1; // intervalo

        else
            return 2; // conjunto
    }
    else
        return -1; // letra normal ou coringa
}

void Automata::makeConnections(){
    int n = this->automataS.length();
    stack<int> p; 
    
    for(int i = 0; i < n; i++){
        int lp = i;

        if(this->automataS[i] == '(' || this->automataS[i] == '|')
            p.push(i); 

        else if(this->automataS[i] == ')'){
            int Or = p.top();
            p.pop();

            if(this->automataS[Or] == '|'){ 
                lp = p.top();
                p.pop();

                addEdge(lp, Or+1);
                addEdge(Or, i);

                if(this->automataS[Or+2] == '*')
                    addEdge(lp, Or+2);
            }
            else
                lp = Or;
        }

        if(i < n-1 && this->automataS[i+1] == '*'){
            addEdge(lp, i+1);
            addEdge(i+1, lp);
        }

        if(i < n-1 && this->automataS[i+1] == '+')
            addEdge(i+1, lp);

        if(i < n-1 && isgraph(this->automataS[i]) && this->automataS[i] != '|')
            addEdge(i, i+1);
    }
}

// adiciona arestas no sentido i -> j
void Automata::addEdge(int i, int j){
    bool skip = false;

    // verifica se ja adicionamos o vertice, evita duplicar
    for(int k = 0; k < this->adjList[i]->listN; k++) 
        if(this->adjList[i]->vList[k]->vertex == j)
            skip = true;
    
    if(!skip){
        Vertex* aux = new Vertex();

        aux->vertex = j;
        aux->letter = this->adjList[j]->letter;
        aux->listN = this->adjList[i]->listN + 1;
        aux->op = this->adjList[j]->op;

        this->adjList[i]->vList.push_back(aux);
        this->adjList[i]->listN++;
    }
}

// busca em profundidade
void Automata::dfsR(int i, bool* marked){
    marked[i] = true;  

    for(int j = 0; j < this->adjList[i]->listN; j++){   
        int w =  this->adjList[i]->vList[j]->vertex;
        if(!marked[w] && this->adjList[i]->lambdaT)
            dfsR(w, marked);
    }
}

// verifica uma palavra - sedgewick
bool Automata::verifyWord(string word){
    int n =(int)word.length();

    bool* visited = new bool[this->V];
    for(int i = 0; i < this->V; i++)
        visited[i] = false;

    dfsR(0, visited); 

    for(int i = 0; i < n; i++){
        bool* atu = new bool[this->V];
        for(int j = 0; j < this->V; j++)
            atu[j] = false;

        for(int j = 0; j < this->V; j++){    

            // -1 letra normal ou coringa
            if(visited[j] && this->adjList[j]->op == -1 && (this->adjList[j]->letter == word[i] || (this->adjList[j]->letter == '.' && this->adjList[j - 1]->letter != '\\')))
                atu[j + 1] = true;

            // 0 - complemento
            else if(visited[j] && this->adjList[j]->op == 0){

                if(this->adjList[j+2]->letter == '-'){ 
                    int start = this->adjList[j+1]->letter;
                    int end = this->adjList[j+3]->letter;

                    if(!(word[i] >= start && word[i] <= end))
                        atu[j+4] = true;
                }
                else{
                    int k = j;
                    bool fits = true;

                    while(this->adjList[k]->letter != ']'){

                        if(this->adjList[k]->letter == word[i])
                            fits = false;
                        k++;
                    }
                    if(fits)
                        atu[k] = true;
                }
            }
            
            // 1 - intervalo
            else if(visited[j] && this->adjList[j]->op == 1){
                int start = this->adjList[j]->letter;
                int end = this->adjList[j + 2]->letter;

                if(word[i] >= start && word[i] <= end)
                    atu[j + 3] = true;
            }

            // 2 - conjunto
            else if(visited[j] && this->adjList[j]->op == 2){
                int k = j;
                bool fits = false;

                while(this->adjList[k]->letter != ']'){

                    if(this->adjList[k]->letter == word[i])
                        fits = true;
                    k++;
                }

                if(fits)
                    atu[k] = true; 
            }

        }

        bool* marked = new bool[this->V];
        for(int j = 0; j < this->V; j++)
            marked[j] = false;

        bool ok = false;

        for(int j = 0; j < this->V; j++){

            if(atu[j]){
                ok = true;
                dfsR(j, marked);
            }
        }
        
        if(atu[this->V-1])
            return true;

        if(!ok)
            return false;

        for(int j = 0; j < this->V; j++)
            visited[j] = marked[j];

        delete(atu);
        delete(marked);
    }

    bool boolR = visited[this->V-1];
    delete(visited);
    return boolR;  
}

// faz a verificação de todas as palavras e printa se é reconhecida ou não
void Automata:: verifyAllWords(){
    for(int i=0; i<this->wordsN; i++){
        if(verifyWord(this->words[i]))
            cout << "S" << endl;
        else
            cout << "N" << endl;
    }
}
