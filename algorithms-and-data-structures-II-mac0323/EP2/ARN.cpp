#include <iostream>
#include <string.h>
#include "no.h"
#include "ARN.h"

using namespace std;

ARN:: ARN(){
    this->tam = 0;
    this->raiz = nullptr;
}

ARN:: ~ARN(){
    daFree(this->raiz);
}

NoARN* ARN:: getRaiz(){
    return this->raiz;
}

void ARN:: daFree(NoARN* raiz){
    if(raiz->esq != nullptr)
        daFree(raiz->esq);
    
    if(raiz->dir != nullptr)
        daFree(raiz->dir);

    delete(raiz);
}

void ARN:: setRaiz(NoARN* raiz){
    this->raiz = raiz;
}

NoARN* ARN:: rodaEsq(NoARN* raiz){
    NoARN* x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = 0; // vermelho
    // atualizou o tamanho das subárvores
    return x;
}

NoARN* ARN:: rodaDir(NoARN* raiz){
    NoARN* x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = 0; // vermelho
    // atualizou o tamanho das subárvores
    return x;
}

void ARN:: trocaCores(NoARN* raiz){
    raiz->cor = 0; // vermelho
    raiz->esq->cor = raiz->dir->cor = 1; // preto
}

NoARN* ARN:: insereARN(NoARN* raiz, string key, Item item){

    // inserção na folha
    if(raiz == nullptr){
        raiz = new NoARN();
        raiz->palavra = key;
        raiz->item = item;
        raiz->esq = raiz->dir = nullptr;
        raiz->cor = 1; // preto

        if(this->tam == 0)
            this->raiz = raiz;

        this->tam++;

        return raiz;
    }

    if(strcmp(key.c_str(), raiz->palavra.c_str()) < 0)
        raiz->esq = insereARN(raiz->esq, key, item);

    else if(strcmp(key.c_str(), raiz->palavra.c_str()) > 0)
        raiz->dir = insereARN(raiz->dir, key, item);

    else 
        raiz->item.qntOcorrencias++;

    if(raiz->esq != nullptr && raiz->dir != nullptr){
        if(raiz->dir->cor == 0 && raiz->esq->cor == 1)
            raiz = rodaEsq(raiz);
        if(raiz->esq->cor == 0 && raiz->esq->esq == 0)
            raiz = rodaDir(raiz);
        if(raiz->esq->cor == 0 && raiz->dir->cor == 0)
            trocaCores(raiz);
    }

    return raiz;
}

void ARN:: add(string key, Item val){
    this->insereARN(this->raiz, key, val);
}

Item ARN:: buscaARN(NoARN *raiz, string key){
    NoARN* raizAux = raiz;
    const char* aux1 = key.c_str();
    const char* aux2 = raizAux->palavra.c_str();

    if(raiz == nullptr){
        // se não está na tabela de símbolos
        Item aux;
        aux.nVogais=-1;
        aux.qntOcorrencias=-1;
        aux.tam=-1;
        return aux;
    }

    if(strcmp(aux1, aux2) == 0)
        return raiz->item;

    if(strcmp(aux1, aux2) < 0)
        return buscaARN(raiz->esq, key);

    return buscaARN(raiz->dir, key);
}

void ARN::inorder(NoARN* raiz){
    
    if(raiz->esq != nullptr)
        inorder(raiz->esq);
    
    cout << raiz->palavra << " " << raiz->item.qntOcorrencias << endl;
    //cout << raiz->palavra << endl;


    if(raiz->dir != nullptr)
        inorder(raiz->dir);
}

void ARN:: imprime(){
    this->inorder(this->raiz);
}

Item ARN:: busca(string key){
    return this->buscaARN(this->raiz, key);  
}