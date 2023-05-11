#include <vector>
#include <string>
#include "item.cpp"

using namespace std;

class No{
    public:
        string key;
        Item item;
        No *fEsq;
        No *fDir;

        No(string key, Item item);
        ~No();
};

class ABB{
    protected:
        int tam;
        No* raiz;

    public:
        ABB();
        ~ABB();
        No* getRaiz();
        No* setNo(string key, Item item);
        void setRaiz(No* raiz);
        No* insereABB(string key, Item item);
        No* buscaABB(No *raiz, string key);
};