#include <vector>
#include <string>
#include "no.h"

#pragma once

using namespace std;

typedef struct No{
    Item item;
    string palavra;
    No* esq;
    No* dir;
};

class ABB{
    protected:
        int tam;
        No* raiz;

    public:
        ABB();
        ~ABB();
        No* getRaiz();
        void daFree(No* raiz);
        void setRaiz(No* raiz);
        No* insereABB(No* raiz, string key, Item item);
        No* buscaABB(No *raiz, string key);
        void inorder(No* raiz);
};