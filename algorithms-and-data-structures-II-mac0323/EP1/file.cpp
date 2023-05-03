#include "file.h"
#include <iostream>
#include <fstream>
#define MAX 256

using namespace std;

File::File(){

}

File::~File(){

}

void File::readFile(){
    fstream testFile;
    char fileName[MAX];

    cout << "Digite o nome do arquivo de teste: " << endl;
    cin >> fileName;

    testFile.open(fileName, ios::in);

    testFile >> this->T;
    testFile >> this->K;
    testFile >> this->Pp;
    testFile >> this->Pd;
    testFile >> this->Pe;
    testFile >> this->C;
    testFile >> this->V;

    testFile.close(); 
}

int File::getT(){
    return T;
}

int File::getK(){
    return K;
}

double File::getPp(){
    return Pp;
}

double File::getPd(){
    return Pd;
}

double File::getPe(){
    return Pe;
}

int File::getC(){
    return C;
}

int File::getV(){
    return V;
}