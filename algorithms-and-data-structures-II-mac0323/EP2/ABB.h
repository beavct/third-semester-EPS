#include <iostream>
#include <string.h>
#include "no.h"

#pragma once

using namespace std;

struct NoABB{
    Item item;
    string palavra;
    NoABB* esq;
    NoABB* dir;
};

class ABB{
    protected:
        int tam;
        NoABB* raiz;

    public:
        ABB();
        ~ABB();
        NoABB* getRaiz();
        void daFree(NoABB* raiz);
        NoABB* insereABB(NoABB* raiz, string key, Item item);
        Item buscaABB(NoABB *raiz, string key);
        void inorder(NoABB* raiz);
        void add(string key, Item val);
        void imprime();
        Item busca(string key);
        void ajudaPalavrasFrequentes(NoABB* raiz, pFrequentesVetor* pf);
};