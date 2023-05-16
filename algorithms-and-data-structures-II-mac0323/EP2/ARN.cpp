#include <bits/stdc++.h>
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

No* ARN:: getRaiz(){
    return this->raiz;
}

void ARN:: daFree(No* raiz){
    if(raiz->esq != nullptr)
        daFree(raiz->esq);
    
    if(raiz->dir != nullptr)
        daFree(raiz->dir);

    free(raiz);
}

void ARN:: setRaiz(No* raiz){
    this->raiz = raiz;
}

No* ARN:: rodaEsq(No* raiz){
    No* x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = 0; // vermelho
    // atualizou o tamanho das subárvores
    return x;
}

No* ARN:: rodaDir(No* raiz){
    No* x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = 0; // vermelho
    // atualizou o tamanho das subárvores
    return x;
}

void ARN:: trocaCores(No* raiz){
    raiz->cor = 0; // vermelho
    raiz->esq->cor = raiz->dir->cor = 1; // preto
}

No* ARN:: insereARN(No* raiz, string key, Item item){

    // inserção na folha
    if(raiz == nullptr){
        raiz = (No*)malloc(sizeof(No));
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

No* ARN:: buscaARN(No *raiz, string key){
    No* raizAux = raiz;
    const char* aux1 = key.c_str();
    const char* aux2 = raizAux->palavra.c_str();

    if(raiz == nullptr || strcmp(aux1, aux2) == 0)
        return raiz;

    if(strcmp(aux1, aux2) < 0)
        return buscaARN(raiz->esq, key);

    return buscaARN(raiz->dir, key);
}

void ARN::inorder(No* raiz){
    
    if(raiz->esq != nullptr)
        inorder(raiz->esq);
    
    cout << raiz->palavra << endl;

    if(raiz->dir != nullptr)
        inorder(raiz->dir);
}