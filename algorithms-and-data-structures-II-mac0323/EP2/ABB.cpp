#include <bits/stdc++.h>
#include "no.h"
#include "ABB.h"

ABB:: ABB(){
    this->tam=0;
    this->raiz = nullptr; // pode ser nullptr
}

ABB:: ~ABB(){
    daFree(this->raiz);
}

void ABB:: daFree(No* raiz){
    if(raiz->esq != nullptr)
        daFree(raiz->esq);
    
    if(raiz->dir != nullptr)
        daFree(raiz->dir);

    free(raiz);
}

No* ABB:: getRaiz(){
    return this->raiz;
}

void ABB:: setRaiz(No* raiz){
    this->raiz = raiz;
}

No* ABB:: insereABB(No* raiz, string key, Item item){

    // inserção na folha
    if(raiz == nullptr){
        raiz = (No*)malloc(sizeof(No));
        raiz->palavra = key;
        raiz->item = item;
        raiz->esq = raiz->dir = nullptr;

        if(this->tam == 0)
            this->raiz = raiz;

        this->tam++;

        return raiz;
    }

    const char* aux1 = key.c_str();
    const char* aux2 = raiz->palavra.c_str();
    // nossa palavra é maior
    if(strcmp(aux1, aux2) > 0){
        raiz->dir = insereABB(raiz->dir, key, item);
        return raiz;
    }

    // nossa palavra é menor
    else if(strcmp(aux1, aux2) < 0){
        raiz->esq = insereABB(raiz->esq, key, item);
        return raiz;
    }
        
    // já temos a palavra na nossa árvore    
    else {
        // são iguais
        raiz->item.qntOcorrencias++;
        return raiz;
    }
}

No* ABB:: buscaABB(No* raiz, string key){
    No* raizAux = raiz;
    const char* aux1 = key.c_str();
    const char* aux2 = raizAux->palavra.c_str();

    if(raiz == nullptr || strcmp(aux1, aux2) == 0)
        return raiz;

    if(strcmp(aux1, aux2) < 0)
        return buscaABB(raiz->esq, key);

    return buscaABB(raiz->dir, key);
}

void ABB::inorder(No* raiz){
    
    if(raiz->esq != nullptr)
        inorder(raiz->esq);
    
    cout << raiz->palavra << endl;

    if(raiz->dir != nullptr)
        inorder(raiz->dir);
}