#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "digraph.h"
#define MAX 256

using namespace std;

int main(){

    Digraph* G = new Digraph;

    G->readDigraph();

    //G->teste();

    //cout << endl << "vamos retirar os ciclos" << endl << endl;

    G->Cycle();

    G->teste();



    return 0;
}