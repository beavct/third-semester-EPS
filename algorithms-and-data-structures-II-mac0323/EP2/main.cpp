#include <bits/stdc++.h>
#include "VO.h"
#include "ABB.h"
#include "TR.h"
#include "ARN.h"
#include "A23.h"

using namespace std;

void leEntrada(string* estrut, int* nPalavras, int* nConsultas){
    fstream file;
    string nomeArq;

    cout << "Digite o nome do arquivo de entrada: ";
    cin >> nomeArq;

    file.open(nomeArq, ios::in);

    file >> estrut;
    file >> nPalavras;

    // lê e coloca na estrutura correta

    file >> nConsultas;

}

int main(){
    char estrut;
    int Npalavras, nConsultas;

    leEntrada(estrut, &nPalavras, &nConsultas);

    return 0;
}