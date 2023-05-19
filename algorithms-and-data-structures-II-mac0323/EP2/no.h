#include <vector>
#include <string>

#pragma once

using namespace std;

struct Item {
    int qntOcorrencias;
    int nVogais;
    int tam;
};

struct pFrequentesVetor{
    vector<string>palavras;
    int nFrequencia = 0;
};
