#include <bits/stdc++.h>
#include "no.h"
#include "A23.h"

using namespace std;

A23:: A23(){
    this->tam=0;
    //this->raiz->tresNo = false;
    //his->raiz->pai = nullptr;
    //this->raiz->dir = this->raiz->esq = nullptr;
    this->raiz = nullptr; // pode ser nullptr
    //cout << "suave" << endl;
}

A23:: ~A23(){
    daFree(this->raiz);
}

void A23:: daFree(NoA23* raiz){
    if(raiz->esq != nullptr)
        daFree(raiz->esq);

    if(raiz->meio != nullptr)
        daFree(raiz->meio);
    
    if(raiz->dir != nullptr)
        daFree(raiz->dir);

    free(raiz);
}

NoA23* A23:: getRaiz(){
    return this->raiz;
}

void A23:: setRaiz(NoA23* raiz){
    this->raiz = raiz;
}

NoA23* A23:: criaNo(string key, Item item){
    NoA23* z = (NoA23*)malloc(sizeof(NoA23));

    //z->pai = pai;
    z->palavra1 = key;
    z->item1 = item;
    z->dir=z->esq=z->meio = nullptr;
    z->tresNo = false;
            
    return z;
}

void A23:: add(string key, Item val){

}

int A23:: ehFolha(NoA23* raiz){
    return (raiz->esq == nullptr && raiz->dir == nullptr);
}

NoA23* A23:: insereA23(NoA23* raiz, string key, Item item){
    // árvore vazia
    if(raiz == nullptr){
        raiz = (NoA23*)malloc(sizeof(NoA23));
        raiz->palavra1 = key;
        raiz->item1 = item;
        raiz->esq = raiz->dir = raiz->meio = nullptr;
        raiz->tresNo = false;

        // verificar se tem que fazer essa comparação ou se pode só colocar que é a raiz
        if(this->tam == 0) 
            this->raiz = raiz;

        this->tam++;

        return raiz;
    } 

    // pensar no caso em que já está na árvore
    // palavra1 == key
    if(strcmp(raiz->palavra1.c_str(), key.c_str()) == 0){
        raiz->item1.qntOcorrencias++;
        return raiz;
    }

    // palavra2 == key
    if(raiz->tresNo)
        if(strcmp(raiz->palavra2.c_str(), key.c_str()) == 0){
            raiz->item2.qntOcorrencias++;
            return raiz;
        }

    this->tam++;

    // se é uma folha só insere
    if(ehFolha(raiz)){
        cout << key << " entrou aq0" << endl;
        
        //return ajudaInserir(raiz, criaNo(key, item));
        raiz = ajudaInserir(raiz, criaNo(key, item));
        return raiz;
    }

    NoA23* aux;

    // key < palavra1 < palavra2 -> insere na esquerda
    if(strcmp(raiz->palavra1.c_str(), key.c_str()) > 0){
        aux = insereA23(raiz->esq, key, item);
        cout << "entrou aq1" << endl;
        // se o filho esquerdo da raiz é o próprio aux
        //cout << key << (aux==raiz->esq) << endl;
        if(aux == raiz->esq)
            return raiz;

        return ajudaInserir(raiz, aux);
    }

    // palavra1 < key
    if((!(raiz->tresNo)) || (strcmp(key.c_str(), raiz->palavra2.c_str())<0)){
        aux = insereA23(raiz->meio, key, item);
        cout << "entrou aq2" << endl;


        if(aux == raiz->meio)
            return raiz;

        return ajudaInserir(raiz, aux);
    }

    // insere na direita
        aux = insereA23(raiz->dir, key, item);
        cout << "entrou aq3" << endl;

        if(aux == raiz->dir)
            return raiz;
        
        return ajudaInserir(raiz, aux);
}

// FAZER ESSA FUNÇÃO
NoA23* A23:: ajudaInserir(NoA23* raiz, NoA23* novo){

    // quando a raiz tem apenas uma chave
    // isso ok
    if(!(raiz->tresNo)){
        if(strcmp(raiz->palavra1.c_str(), novo->palavra1.c_str()) < 0){
            cout << "cavalo1" << endl;
            raiz->palavra2 = novo->palavra1;
            raiz->item2 = novo->item1;

            raiz->meio = novo->esq;
            raiz->dir = novo->meio;
        }

        else{
            cout << "cavalo2" << endl;
            raiz->palavra2 = raiz->palavra1;
            raiz->item2 = raiz->item1;
            raiz->dir = raiz->meio;


            raiz->palavra1 = novo->palavra1;
            raiz->item1 = novo->item1;

            raiz->meio = novo->meio;
        }

        raiz->tresNo = true;

        return raiz;
    }

    // nossa raiz já é tresNo
    // adiciona à esquerda
    // key < palavra1 < palavra2
    if(strcmp(raiz->palavra1.c_str(), novo->palavra1.c_str()) > 0){
        NoA23* aux = criaNo(raiz->palavra1, raiz->item1);
        aux->esq = novo;
        aux->meio = raiz;

        novo->esq = raiz->esq;

        raiz->esq = raiz->meio;
        raiz->meio = raiz->dir;
        raiz->dir = nullptr;

        raiz->palavra1 = raiz->palavra2;
        raiz->item1 = raiz->item2;
        raiz->tresNo = false;

        return aux;
    }

    // adicionar no centro
    // palavra1 < key < palavra2
    if(strcmp(raiz->palavra2.c_str(), novo->palavra1.c_str()) > 0){
        cout << "adicionou " << novo->palavra1 << " no centro" << endl;
        /*novo->meio = criaNo(raiz->palavra2, raiz->item2);
        novo->meio->esq = novo->meio;

        novo->meio->meio = raiz->dir;

        novo->esq = raiz;

        raiz->dir = nullptr;
        raiz->tresNo = false;*/
        
        novo->esq = criaNo(raiz->palavra1, raiz->item1);



        novo->dir = criaNo(raiz->palavra2, raiz->item2);


        return novo;
    }

    // adiciona à direita
    NoA23* aux = criaNo(raiz->palavra2, raiz->item2);
    aux->esq = raiz;
    aux->meio = novo;

    novo->esq = raiz->dir;
    raiz->dir = nullptr;
    raiz->tresNo = false;
    
    return aux;
}

Item A23:: buscaA23(NoA23* raiz, string key){
    // acho que ta certo
    const char* aux1 = key.c_str();
    const char* aux2 = raiz->palavra1.c_str();
    const char* aux3 = raiz->palavra2.c_str();

    if(raiz == nullptr){
        // se não está na tabela de símbolos
        Item aux;
        aux.nVogais=-1;
        aux.qntOcorrencias=-1;
        aux.tam=-1;
        return aux;
    }

    if(strcmp(aux1, aux2) == 0 )
        return raiz->item1;
    
    
    if((raiz->tresNo) && strcmp(aux1, aux3) == 0)
        return raiz->item2;
    

    if(strcmp(aux1, aux2) < 0)
        return buscaA23(raiz->esq, key);

    if(raiz->tresNo && strcmp(aux1, aux2) < 0 && strcmp(aux1, aux3) > 0)
        return buscaA23(raiz->meio, key);

    return buscaA23(raiz->dir, key);
}

void A23::inorder(NoA23* raiz){
    cout << "tamanho: " << this->tam << endl;
    //cout << "oiee" << endl;
    if(raiz->esq != nullptr)
        inorder(raiz->esq);

    cout << raiz->palavra1 << endl;

    if(raiz->tresNo) {
        if(raiz->meio != nullptr)
        inorder(raiz->dir);
        cout << raiz->palavra2 << endl;
    }

    if(raiz->dir != nullptr)
            inorder(raiz->meio);
}


void A23:: viz(NoA23* node)
{
    if (node == nullptr)
    {
        return;
    }

    std::cout << node->palavra1 << "[label=\"" << node->palavra1;

    if (!node->tresNo)
    {
        std::cout << " " << node->palavra2;
    }

    std::cout << "\"];\n\n";

    if (node->esq != nullptr)
    {
        std::cout << node->palavra1 << " -> " << node->esq->palavra1 << "\n";
        std::cout << node->palavra1 << " -> " << node->meio->palavra1 << "\n";
    }
    if (node->dir != nullptr)
    {
        std::cout << node->palavra1 << " -> " << node->dir->palavra1 << "\n";
    }

    viz(node->esq);
    viz(node->meio);
    viz(node->dir);
}

/*void A23::inorder(NoA23* raiz){
    cout << "tamanho: " << this->tam << endl;  
    cout << raiz->tresNo << endl;
    // acho que ta certo
    if(raiz->esq != nullptr)
        inorder(raiz->esq);

    cout << raiz->palavra1 << endl;

    if(raiz->tresNo) {
        if(raiz->meio != nullptr)
            inorder(raiz->meio);
        cout << raiz->palavra2 << endl;
    }

    if(raiz->dir != nullptr)
        inorder(raiz->dir);


    OUU
    cout << "tamanho: " << this->tam << endl;  

    if(raiz->esq != nullptr)
        inorder(raiz->esq);

    cout << raiz->palavra1 << endl;

        if(raiz->meio != nullptr)
            inorder(raiz->meio);
        cout << raiz->palavra2 << endl;

    if(raiz->dir != nullptr)
        inorder(raiz->dir);
}*/