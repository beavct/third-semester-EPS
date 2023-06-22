#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "testGenerator.h"

using namespace std;

TestGenerator:: TestGenerator(){

}

TestGenerator:: ~TestGenerator(){

}

void TestGenerator:: oiee(){
    int i, j;

    srand(time(0));

    this->sequenceSize = (rand() % 50) + 2;

    string oieee = "ACGT";

    //cout << this->sequenceSize << endl;

    int cida = this->sequenceSize;

    for(i=0; i < cida; i++){
        
        int cavalo = rand() % 4; 

        this->sequence[i] = oieee[cavalo];
    }

    this->quantFrag = (rand() % (this->sequenceSize - 2)) + 1;

    fstream File;
    string filename;

    cout << "Digite o nome desejado para a saída: ";
    cin >> filename;
        cout << "oiee" << endl;

    File.open(filename, ios::out);

    File << this->quantFrag << endl;

    for(i=0; i<this->quantFrag; i++){
    
        int ini = rand() % (this->sequenceSize-2);
        int tam = rand() % (this->sequenceSize-ini);

        for(j=ini; j<ini+tam; j++){
            File << this->sequence[j];
        }

        File << endl;
    }

    File << this->sequence;

    File.close();

}

int main(){
    TestGenerator* oiee = new TestGenerator();

    oiee->oiee();

    return 0;
}