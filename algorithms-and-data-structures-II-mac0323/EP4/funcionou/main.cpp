#include <iostream>
#include <string>
#include "regexp.h"

using namespace std;

int main(int argc, char* argv[]){

    if(argc < 2){
        cout << "Indique o arquivo de leitura da entrada" << endl;
        return 0;
    }

    string filename;

    filename = argv[1];


    Automata* Oie = new Automata();
    Oie->readInput(filename);
    Oie->createVertex();
    Oie->makeConnections();
    Oie->verifyAllWords();

    return 0;
}