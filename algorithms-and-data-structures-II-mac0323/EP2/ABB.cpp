#include <vector>
#include <string>
#include "item.cpp"
#include "ABB.h"

No:: No(string key, Item item){
    this->key = key;
    this->item = item;
    this->fDir = this->fEsq = nullptr;
}

No:: ~No(){

}

ABB:: ABB(){
    this->tam=0;
    this->raiz = nullptr; // pode ser nullptr
}

ABB:: ~ABB(){

}

No* ABB:: getRaiz(){
    return this->raiz;
}

No* ABB:: setNo(string key, Item item){
    this->raiz->item = item;
    this->raiz->key = key;
    this->raiz->fEsq = this->raiz->fDir = nullptr;
    return this->raiz;
}

void ABB:: setRaiz(No* raiz){
    this->raiz = raiz;
}

No* ABB:: insereABB(string key, Item item){
    No* raizAux = this->getRaiz();

    if(raizAux == nullptr){
        this->setRaiz(this->setNo(key, item));
        this->tam++;
        return raizAux;
    }
    if(key < raizAux->key)
        

}

No* ABB:: buscaABB(No *raiz, string key){
    No* raizAux = raiz; // usar o getNo() na hora da passagem do parametro
    if(raizAux == nullptr || raizAux->key == key)
        return raizAux;

    if(key < raizAux->key)
        return buscaABB(raizAux->fEsq, key);
    return buscaABB(raizAux->fDir, key);
}