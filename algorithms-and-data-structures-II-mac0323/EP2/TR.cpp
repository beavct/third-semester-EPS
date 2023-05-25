#include <iostream>
#include <string.h>
#include "no.h"
#include "TR.h"

using namespace std;

TR:: TR(){
    this->tam = 0;
    this->raiz = nullptr;
}

TR:: ~TR(){
    delete(this->raiz);
}

void TR:: daFree(NoTR* raiz){
    if(raiz->esq != nullptr)
        daFree(raiz->esq);
    
    if(raiz->dir != nullptr)
        daFree(raiz->dir);

    free(raiz);
}

NoTR* TR:: getRaiz(){
    return this->raiz;
}

NoTR* TR:: rodaEsq(NoTR* raiz){
    NoTR* auxD = raiz->dir;
    NoTR* auxE = raiz->dir->esq;

    auxD->esq = raiz;
    raiz->dir = auxE;

    // nova raiz
    return auxD;
}

NoTR* TR:: rodaDir(NoTR* raiz){
    NoTR* auxE = raiz->esq;
    NoTR* auxD = raiz->esq->dir;

    auxE->dir = raiz;
    raiz->esq = auxD;

    // nova raiz
    return auxE; 
}

NoTR* TR:: insereTR(NoTR* raiz, string key, Item item){
    if(raiz == nullptr){
        raiz = new NoTR();
        raiz->palavra = key;
        raiz->item = item;
        raiz->esq = raiz->dir = nullptr;

        srand(time(nullptr));
        raiz->prioridade = rand() % INTMAX_MAX;

        if(this->tam == 0)
            this->raiz = raiz;
            
        this->tam++;

        return raiz;
    }

    const char* aux1 = key.c_str();
    const char* aux2 = raiz->palavra.c_str();

    if(strcmp(aux1, aux2) == 0){
    // as duas palavras são iguais 
        raiz->item.qntOcorrencias++;
        return raiz;

    }

    // nossa palavra é maior
    else if(strcmp(aux1, aux2) > 0){
        raiz->dir = insereTR(raiz->dir, key, item);

        // consertar a prioridade de max heap
        if(raiz->dir != nullptr && raiz->dir->prioridade > raiz->prioridade)
            raiz = rodaEsq(raiz);

        return raiz;
    }

    // nossa palavra é menor
    //else if(strcmp(aux1, aux2) < 0){
        raiz->esq = insereTR(raiz->esq, key, item);

        // consertar a prioridade de max heap
        if(raiz->esq != nullptr && raiz->esq->prioridade > raiz->prioridade)
            raiz = rodaDir(raiz);

        return raiz;

}

Item TR:: buscaTR(NoTR *raiz, string key){
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
        return buscaTR(raiz->esq, key);

    return buscaTR(raiz->dir, key);
}

void TR:: add(string key, Item val){
    this->raiz = this->insereTR(this->raiz, key, val);
}

void TR::inorder(NoTR* raiz){
    
    if(raiz->esq != nullptr)
        inorder(raiz->esq);
    
    //cout << raiz->palavra << " " << raiz->item.qntOcorrencias << endl;
    cout << raiz->palavra << endl;

    if(raiz->dir != nullptr)
        inorder(raiz->dir);
}

void TR:: imprime(){
    this->inorder(this->raiz);
}

Item TR:: busca(string key){
    return this->buscaTR(this->raiz, key);
}

void TR:: ajudaPalavrasFrequentes(NoTR* raiz, pFrequentesVetor* pf){
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
