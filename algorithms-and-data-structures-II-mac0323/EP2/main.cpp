#include <bits/stdc++.h>
#include "no.h"
// #include "VO.h" // a estrutura básica ta ok
// #include "ABB.h" // a estrutura básica ta ok
// #include "TR.h" // a estrutura básica ta ok
#include "ARN.h"
// #include "A23.h"

using namespace std;

int contaVogais(string s){
    int Af, Ef, If, Of, Uf;
    int j=0;
    Af=Ef=If=Of=Uf=0;

    for(int i=0; i<strlen(s.c_str()) && j!=5; i++){

        if(Af==0 && (s[i] == 'A' || s[i] == 'a')){
            Af=1;
            j++;
        }

        if(Ef==0 && (s[i] == 'E' || s[i] == 'e')){
            Ef=1;
            j++;
        }

        if(If==0 && (s[i] == 'I' || s[i] == 'i')){
            If=1;
            j++;
        }

        if(Of==0 && (s[i] == 'O' || s[i] == 'o')){
            Of=1;
            j++;
        }

        if(Uf==0 && (s[i] == 'U' || s[i] == 'u')){
            Uf=1;
            j++;
        }

    }

    return j;
}

int main(){
    // instância os objetos
    ARN arvoreRN;

    // lê entrada do arquivo indicado
    int nPalavras, nConsultas;
    fstream file;
    string nomeArq, estrut, palavra;
    string  remover = "'!@#$%*()+=§[]{}|<>,.:;?/"; 

    cout << "Digite o nome do arquivo de entrada: ";
    cin >> nomeArq;

    file.open(nomeArq.c_str());

    file >> estrut;
    file >> nPalavras;


    // leitura e limpeza das palavras está ok
    for(int i = 0; i<nPalavras; i++){
        string palavra;
        Item aux;

        file >> palavra;

        for(char c: remover)
            palavra.erase(remove(palavra.begin(), palavra.end(), c), palavra.end());

        aux.tam = strlen(palavra.c_str());
        aux.qntOcorrencias = 1;
        aux.nVogais = contaVogais(palavra);

        // insere
        arvoreRN.insereARN(arvoreRN.getRaiz(), palavra, aux);
    }

    // lê e coloca na estrutura correta

    file >> nConsultas;
    file.close();

    // printa na ordem 
    arvoreRN.inorder(arvoreRN.getRaiz());

    return 0;
}