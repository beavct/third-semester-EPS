#include <bits/stdc++.h>
#include "no.h"
#include "TR.h"

using namespace std;

TR:: TR(){
    this->tam = 0;
    this->raiz = nullptr;
}

TR:: ~TR(){
    daFree(this->raiz);
}

void TR:: daFree(No* raiz){
    if(raiz->esq != nullptr)
        daFree(raiz->esq);
    
    if(raiz->dir != nullptr)
        daFree(raiz->dir);

    free(raiz);
}

No* TR:: getRaiz(){
    return this->raiz;
}

void TR:: setRaiz(No* raiz){
    this->raiz = raiz;
}

No* TR:: rodaEsq(No* raiz){
    No* auxD = raiz->dir;
    No* auxE = auxD->esq;

    auxD->esq = raiz;
    raiz->dir = auxE;

    // nova raiz
    return auxD;
}

No* TR:: rodaDir(No* raiz){
    No* auxE = raiz->esq;
    No* auxD = auxE->dir;

    auxE->dir = raiz;
    raiz->esq = auxD;

    // nova raiz
    return auxE;  

}

No* TR:: insereTR(No* raiz, string key, Item item){
    if(raiz == nullptr){
        raiz = (No*)malloc(sizeof(No));
        raiz->palavra = key;
        raiz->item = item;
        raiz->esq = raiz->dir = nullptr;

        srand(time(0));
        raiz->prioridade = rand() % INT_MAX;

        this->tam++;

        return raiz;
    }

    const char* aux1 = key.c_str();
    const char* aux2 = raiz->palavra.c_str();

    // nossa palavra é maior
    if(strcmp(aux1, aux2) > 0){
        raiz->dir = insereTR(raiz->dir, key, item);

        // consertar a prioridade de max heap
        if(raiz->dir->prioridade > raiz->prioridade)
            raiz = rodaEsq(raiz);

        return raiz;
    }

    // nossa palavra é menor
    else if(strcmp(aux1, aux2) < 0){
        raiz->esq = insereTR(raiz->esq, key, item);

        // consertar a prioridade de max heap
        if(raiz->esq->prioridade > raiz->prioridade)
            raiz = rodaDir(raiz);

        return raiz;
    }

    else{ // as duas palavras são iguais 
        raiz->item.qntOcorrencias++;
        return raiz;
    }

}

No* TR:: buscaTR(No *raiz, string key){
    No* raizAux = raiz;
    const char* aux1 = key.c_str();
    const char* aux2 = raizAux->palavra.c_str();

    if(raiz == nullptr || strcmp(aux1, aux2) == 0)
        return raiz;

    if(strcmp(aux1, aux2) < 0)
        return buscaTR(raiz->esq, key);

    return buscaTR(raiz->dir, key);
}
