#include <vector>
#include <string>
#include <vector>
#include "vo.h"
#include "item.cpp"

VO:: VO(){

}

VO:: ~VO(){

}

int VO:: getQntPalavras(){
    return this->qntPalavras;
}

void VO:: insere(Key key, Item val){
    for(int i=0; i < this->qntPalavras; i++){
        // nossa chave ainda é maior
        if(strcmp(key, this->palavras[i]->getKey()) > 0) 
            continue;
        // nossa palavra é menor
        else if(strcmp(key, this->palavras[i]->getKey()) < 0){ 
            for(int j = this->qntPalavras - 1; j<=i; j--){
                this->palavras[j+1]=this->palavras[j];
            }
            this->palavras[i]->key = key;
            this->palavras[i]->val = val;
        }
        // strcmp(key, this->palavras[i].key) == 0
        else{
            Item aux = this->palavras[i]->getValue();
            aux->setNOcorrencias(aux->getNOcorrencias()+1);
            this->palavras[i]->setValue(aux);
            break;
        }
    }
}

Item VO:: busca(Key key){
    for(int i = 0; i < this->qntPalavras; i++){
        if(this->palavras[i]->getKey() == key){
            return this->palavras[i]->getValue();
            break;
        }
    }
    return nullptr;
}
