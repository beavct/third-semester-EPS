#include <iostream>
#include <string>
#include "no.h"

using namespace std;

struct NoARN{
    Item item;
    string palavra;
    int cor; 
    // 1: preto
    // 0: vermelho
    NoARN* esq;
    NoARN* dir;
};

class ARN{
    protected:
        int tam;
        NoARN* raiz;
    public:
        ARN();
        ~ARN();
        NoARN* getRaiz();
        void daFree(NoARN* raiz);
        void setRaiz(NoARN* raiz);
        NoARN* rodaEsq(NoARN* raiz);
        NoARN* rodaDir(NoARN* raiz);
        NoARN* insereARN(NoARN* raiz, string key, Item item);
        Item buscaARN(NoARN *raiz, string key);
        void inorder(NoARN* raiz);
        void trocaCores(NoARN* raiz);
        void add(string key, Item val);
};