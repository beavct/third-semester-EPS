#include <bits/stdc++.h>
#include "no.h"
#include "VO.h"

using namespace std;

VO:: VO(){
    this->palavras = (Palavras*)malloc(sizeof(Palavras)*2);
    this->max=2;
    this->qntPalavras=0;
}

VO:: ~VO(){
    free(this->palavras);
}

void VO:: resize(){
    this->max = 2*this->max;
    this->palavras = (Palavras*)realloc(this->palavras, sizeof(Palavras)*this->max);
}

int VO:: getQntPalavras(){
    return this->qntPalavras;
}

// vetor ordenado em ordem crescente
void VO:: insere(string key, Item val){
    // pro c++ parar de xiar
    const char *aux1 = key.c_str(); 

    for(int i=0; i < this->qntPalavras; i++){
        // pro c++ parar de xiar
        const char *aux2 = this->palavras[i].palavra.c_str();

        // nossa chave ainda é menor
        if(strcmp(aux1, aux2) < 0) 
            continue;
            
        // nossa palavra é maior
        else if(strcmp(aux1, aux2) > 0){ 
            if(this->qntPalavras == this->max)
                resize();

            for(int j = this->qntPalavras - 1; j<=i; j--){
                this->palavras[j+1]=this->palavras[j];
            }
            this->palavras[i].palavra = key;
            this->palavras[i].item = val;
            this->qntPalavras++;
            break;
        }

        // strcmp(key, this->palavras[i].key) == 0
        else{
            this->palavras[i].item.qntOcorrencias++;
            break;
        }
    }
}

Item VO:: busca(string key){
    for(int i = 0; i < this->qntPalavras; i++){
        if(this->palavras[i].palavra == key){
            return this->palavras[i].item;
            break;
        }
    }

    // se não está na tabela de símbolos
    Item aux;
    aux.nVogais=-1;
    aux.qntOcorrencias=-1;
    aux.tam=-1;
    return aux;
}


