#include <iostream>
#include <string>
#include "no.h"

using namespace std;

struct NoTR{
    Item item;
    string palavra;
    int prioridade;
    NoTR* esq;
    NoTR* dir;
};

class TR{
    protected:
        int tam;
        NoTR* raiz;

    public:
        TR();
        ~TR();
        NoTR* getRaiz();
        void daFree(NoTR* raiz);
        void setRaiz(NoTR* raiz);
        NoTR* rodaEsq(NoTR* raiz);
        NoTR* rodaDir(NoTR* raiz);
        NoTR* insereTR(NoTR* raiz, string key, Item item);
        Item buscaTR(NoTR *raiz, string key);
        void inorder(NoTR* raiz);
        void add(string key, Item val);
};