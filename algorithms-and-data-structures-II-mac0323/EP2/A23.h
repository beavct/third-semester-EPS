#include <vector>
#include <string>
#include "no.h"

#pragma once

using namespace std;

struct NoA23{
    Item item1;
    string palavra1;
    Item item2;
    string palavra2;
    bool tresNo;
    //No* pai;
    NoA23* esq;
    NoA23* meio;
    NoA23* dir;
};

class A23{
    protected:
        int tam;
        NoA23* raiz;

    public:
        A23();
        ~A23();
        NoA23* getRaiz();
        void daFree(NoA23* raiz);
        void setRaiz(NoA23* raiz);
        NoA23* insereA23(NoA23* raiz, string key, Item item);
        Item buscaA23(NoA23 *raiz, string key);
        void inorder(NoA23* raiz);
        NoA23* criaNo(string key, Item item);
        void add(string key, Item val);
        //NoA23* ajuda(NoA23* raiz, string key, Item item);
        int ehFolha(NoA23* raiz);
        NoA23* ajudaInserir(NoA23* raiz, NoA23* novo);
        void viz(NoA23* node);
};