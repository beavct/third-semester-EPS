#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <ctype.h>
#include "regexp.h"

using namespace std;

Automata:: Automata(){
    this->V = 0;
}

// deleta os vetores utilizados
Automata:: ~Automata(){
    for (int i=0; i<this->V; i++)
        delete(this->symbols[i].edges);
    delete(this->symbols);
    delete(this->words);
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

// faz a verificação de todas as palavras e printa se é reconhecida ou não
void Automata:: verifyAllWords(){
    for(int i=0; i<this->wordsN; i++){
        if(verifyWord(this->words[i]))
            cout << "S" << endl;
        else
            cout << "N" << endl;
    }
}

// faz a verificação de uma palavra, sedgewick
bool Automata:: verifyWord(string word){
    // tratamento para string vazia
    if(word == "" && this->symbols[this->V-1].symbol == '*')
        return true;

    int n = (int)word.length();

    bool* visited = new bool[this->V];
    for(int i=0; i<this->V; i++)
        visited[i] = false;

    dfsR(0, visited);
    // TIRAT DPS
    cout << "visited" << endl;
    for(int j=0; j<this->V; j++){
        cout << visited[j] << " ";
    }
    cout << endl;

    for(int i=0; i<n; i++){
        bool* atu = new bool[this->V];
        
        for(int j=0; j<this->V; j++)
            atu[j] = false;

        for(int j=0; j<this->V; j++){
            // -1 - não é operação não básica ([], [-], [^])
            if(visited[j] && this->symbols[j].op == -1 && (this->automataS[j] == word[i] || (this->symbols[j].symbol = '.' && this->symbols[j-1].symbol != '\\'))){
                //cout << endl << (this->automataS[j]) << endl << endl;
                //cout << endl << (j+1) << endl << endl;
                atu[j+1] = true;
            }

            // 0 - complemento
            else if(visited[j] && this->symbols[j].op == 0){
                if(this->symbols[j+2].symbol == '-'){
                    int start = this->symbols[j+1].symbol;
                    int end = this->symbols[j+3].symbol;

                    if(!(word[i] >= start && word[i] <= end))
                        atu[j+4] = true;
                }

                else{
                    int save = j;
                    bool fits = true;

                    while(this->symbols[save].symbol != ']'){
                        if(word[i] == this->symbols[save].symbol){
                            fits = false;
                        }
                        save++;
                    }
                    if(fits)
                        atu[save] = true;
                }
            }

            // 1 - intervalo
            else if(visited[j] && this->symbols[j].op == 1){
                int start = this->symbols[j].symbol;
                int end = this->symbols[j+2].symbol;

                if(word[i] >= start && word[i] <= end)
                    atu[j+3] = true; 
            }

            // 2 - conjunto
            else if(visited[j] && this->symbols[j].op == 2){
                int save = j;
                bool fits = false;

                while(this->symbols[save].symbol != ']'){
                    if(this->symbols[save].symbol == word[i]){
                        fits = true;
                    }
                    save++;
                }

                if(fits)
                    atu[save] = true;
            }


        }
        // TIRAT DPS
        cout << "atu" << endl;
        for(int j=0; j<this->V; j++){
            cout << atu[j] << " ";
        }

        bool* marked = new bool[this->V];
        for(int j=0; j<this->V; j++)
            marked[j] = false;

        bool ok = false;

        for(int j=0; j<this->V; j++){
            if(atu[j]){
                ok = true;
                dfsR(j, marked);
            }
        }
        // TIRAT DPS
        if(atu[this->V-1]){
            cout << "entrou1" << endl;
            return true;
        }
        // TIRAT DPS
        // não chegamos no prox caracter
        if(!ok){
            cout << "entrou2" << endl;
            return false;
        }
        
        for(int j=0; j<this->V; j++){
            visited[j] = marked[j];
        }

        // TIRAT DPS
        cout << endl;
        cout << "marked" << endl;
        for(int j=0; j<this->V; j++){
            cout << marked[j] << " ";
        }
        cout << endl;

        delete[] marked;
        delete[] atu;
    }

    bool boolR = visited[this->V-1];
    delete [] visited;
    return boolR;
}

// busca em profundidade
void Automata:: dfsR(int i, bool* visited){
    visited[i] = true;

    for(int j=0; j<this->symbols[i].edgesN; j++){
        int w = this->symbols[i].edges[j]->index;
        if(!visited[w] && this->symbols[i].lambdaT){
            dfsR(w, visited);
        }
    }
}

// printa os vértices e suas conexões
void Automata:: teste(){
    cout << this->automataS << endl << endl;
    for(int i=0; i<this->V; i++){
        cout << this->symbols[i].symbol << "  ";
        cout << i << " " << this->symbols[i].lambdaT;
        for (int j=0; j<this->symbols[i].edgesN; j++){
            //int w = this->symbols[j].edges[j]->index;
            cout << " -> " << this->symbols[i].edges[j]->symbol << " " << this->symbols[i].edges[j]->index;
        }

        cout << endl;
    }
    cout << "------";

    cout << endl << endl;

    for(int i=0; i<this->wordsN; i++)
        cout << this->words[i] << endl;
}

// cria os vértices do automoto, sem nenhuma aresta
void Automata:: createVertex(){
    int auxI = (int)this->automataS.length();

    this->symbols = new vertex[auxI];

    for(int i=0; i<auxI; i++){
            this->symbols[i].symbol = this->automataS[i];
            this->symbols[i].index = i;
            this->symbols[i].edgesN = 0;
            this->symbols[i].edges = new vertex*[auxI];
            this->symbols[i].op = defineOp(i);
            this->symbols[i].lambdaT = defineLambdaT(i);
    }
    this->V = auxI;
}

// define se o caracter da expressão regular é um símbolo a ser consumido ou uma operação que possui transição lambda
bool Automata:: defineLambdaT(int i){
    if(this->automataS[i] == '|' || this->automataS[i] == '(' || this->automataS[i] == ')' || this->automataS[i] == '[' || this->automataS[i] == ']' || this->automataS[i] == '+' || this->automataS[i] == '*' || this->automataS[i] == '\\'){
        if(i==0)
            return true;
        else if(this->automataS[i-1] != '\\')
            return true;

    }

    return false;
}

// define se o caracter é alguma operação não básica ([^], [-], [])
int Automata:: defineOp(int i){
    if(this->automataS[i-1] == '['){
        if(this->automataS[i] == '^')
            return 0; // complemento
        else if(this->automataS[i+1] == '-')
            return 1; // intervalo
        else   
            return 2; // conjunto
    }

    

    return -1; // nenhuma das opções anteriores
}

// cria as arestas do automoto
void Automata:: makeConnections(){
    stack<int> p;
    int n = (int)this->automataS.length();

    for(int i=0; i<n; i++){
        int lp = i;

        if(this->symbols[i].symbol == '(' || this->symbols[i].symbol == '|')
            p.push(i);
        
        else if(this->symbols[i].symbol == ')'){
            int Or = p.top();
            p.pop();
            
            if(this->symbols[Or].symbol == '|'){
                lp = p.top();
                p.pop();

                addEdge(lp, Or+1);

                if(this->symbols[Or+2].symbol == '*')
                    addEdge(lp, Or+2);
                addEdge(Or, i);
            }
            else
                lp = Or;
        }

        if(i < n-1 && this->symbols[i+1].symbol == '*'){
            addEdge(lp, i+1);
            addEdge(i+1, lp);
        }

        if(i< n-1 && this->symbols[i+1].symbol == '+')
            addEdge(i+1, lp);

        if(i < n-1 && isgraph(this->symbols[i].symbol) && this->symbols[i].symbol != '|') 
            addEdge(i, i+1);
    }
    
}

// adiciona aresta no sentido i -> j
void Automata:: addEdge(int i, int j){
    bool jump = false;

    // evitar arestas duplicadas
    for(int k=0; k<this->symbols[i].edgesN; k++){
        if(this->symbols[i].edges[k]->index == this->symbols[j].index){
            jump = true;
            break;
        }
    }

    if(!jump)
        this->symbols[i].edges[this->symbols[i].edgesN++] = &this->symbols[j];
}