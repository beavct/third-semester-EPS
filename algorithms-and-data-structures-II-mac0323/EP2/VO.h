#include <iostream>
#include <string>
#include "no.h"

#pragma once

using namespace std;

typedef struct {
    Item item;
    string palavra;
}Palavras;

class VO{
    protected:
        int max; // quantidade máxima de palavras que podem ser guardadas no vetor
        int qntPalavras; // guarda a quantidade de palavras no vetor
        Palavras *palavras; // bloco com as palavras + suas informações
    public:
        VO();
        ~VO();
        void resize();
        int getQntPalavras();
        void insere(string key, Item val);
        Item busca(string key);
        void inorder();
        void quickSort(int ini, int fim); // depois que insere tem que fazer o quickSort
        int particiona(int ini, int fim);
        void add(string key, Item val);
};

