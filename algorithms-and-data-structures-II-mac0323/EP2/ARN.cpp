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
    No* auxD = raiz->dir;
    No* auxE = auxD->esq;

    auxD->esq = raiz;
    raiz->dir = auxE;

    // nova raiz
    return auxD;
}

No* ARN:: rodaDir(No* raiz){
    No* auxE = raiz->esq;
    No* auxD = auxE->dir;

    auxE->dir = raiz;
    raiz->esq = auxD;

    // nova raiz
    return auxE;  

}

No* ARN:: insereARN(No* raiz, string key, Item item){
    if(raiz == nullptr){
        raiz = (No*)malloc(sizeof(No));
        raiz->palavra = key;
        raiz->item = item;
        raiz->esq = raiz->dir = nullptr;
        raiz->cor = 0; // sempre insere como vermelho
        this->tam++;

        return raiz;
    }

    const char* aux1 = key.c_str();
    const char* aux2 = raiz->palavra.c_str();

    // nossa palavra é maior
    if(strcmp(aux1, aux2) > 0){
        raiz->dir = insereARN(raiz->dir, key, item);



        return raiz;
    }

    // nossa palavra é menor
    else if(strcmp(aux1, aux2) < 0){
        raiz->esq = insereARN(raiz->esq, key, item);

        // não fiz a putaria de vermelho preto e os caraio

        return raiz;
    }

    else{ // as duas palavras são iguais 
        raiz->item.qntOcorrencias++;
        return raiz;
    }

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


