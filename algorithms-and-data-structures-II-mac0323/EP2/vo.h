#include <vector>
#include <string>
#include "item.cpp"

template <class Key, class Item>
class VO{
    protected:
        int qntPalavras; // guarda a quantidade de palavras no vetor
        vector<Palavra> palavras; // bloco com as palavras + suas informações
    public:
        VO();
        ~VO();
        int getQntPalavras();
        void insere(Key key, Item val);
        Item busca(Key key);
};

