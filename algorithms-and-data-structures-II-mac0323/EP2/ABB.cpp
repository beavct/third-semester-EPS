#include <iostream>
#include <string.h>
#include "no.h"
#include "ABB.h"

ABB:: ABB(){
    this->tam=0;
    this->raiz = nullptr; // pode ser nullptr
}

ABB:: ~ABB(){
    daFree(this->raiz);
}

void ABB:: daFree(NoABB* raiz){
    if(raiz->esq != nullptr)
        daFree(raiz->esq);
    
    if(raiz->dir != nullptr)
        daFree(raiz->dir);

    delete(raiz);
}

NoABB* ABB:: getRaiz(){
    return this->raiz;
}

NoABB* ABB:: insereABB(NoABB* raiz, string key, Item item){

    // inserção na folha
    if(raiz == nullptr){
        raiz = new NoABB();
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

Item ABB:: buscaABB(NoABB* raiz, string key){
    const char* aux1 = key.c_str();

    if(raiz == nullptr){
        // se não está na tabela de símbolos
        Item aux;
        aux.nVogais=0;
        aux.qntOcorrencias=0;
        aux.tam=0;
        return aux;
    }

    const char* aux2 = raiz->palavra.c_str();
    
    if(strcmp(aux1, aux2) == 0)
        return raiz->item;

    if(strcmp(aux1, aux2) < 0)
        return buscaABB(raiz->esq, key);

    return buscaABB(raiz->dir, key);
}

void ABB:: add(string key, Item val){
    this->insereABB(this->raiz, key, val);
}

void ABB::inorder(NoABB* raiz){
    
    if(raiz->esq != nullptr)
        inorder(raiz->esq);
    
    cout << raiz->palavra << " " << raiz->item.qntOcorrencias << endl;
    //cout << raiz->palavra << endl;

    if(raiz->dir != nullptr)
        inorder(raiz->dir);
}

void ABB:: imprime(){
    this->inorder(this->raiz);
}

Item ABB:: busca(string key){
    return this->buscaABB(this->raiz, key);
}

void ABB:: ajudaPalavrasFrequentes(NoABB* raiz, pFrequentesVetor* pf){
    if(raiz->esq != nullptr)
        ajudaPalavrasFrequentes(raiz->esq, pf);
    
    if(raiz->item.qntOcorrencias > pf->nFrequencia){
        pf->palavras.clear();
        pf->palavras.push_back(raiz->palavra);
        pf->nFrequencia = raiz->item.qntOcorrencias;
    }
    else if(raiz->item.qntOcorrencias == pf->nFrequencia){
        pf->palavras.push_back(raiz->palavra);
    }

    if(raiz->dir != nullptr)
        ajudaPalavrasFrequentes(raiz->dir, pf);
}