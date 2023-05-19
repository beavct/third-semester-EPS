#include <iostream>
#include <string.h>
#include <vector>
#include "no.h"
#include "VO.h"

using namespace std;

VO:: VO(){
    this->itens = (Item*)calloc(2,sizeof(Item)*2);
    this->palavras = (string*)calloc(2, sizeof(string)*2);
    this->max=2;
    this->qntPalavras=0;
}

VO:: ~VO(){
    free(this->palavras);
    free(this->itens);
}

void VO:: resize(){
    this->max *= 2;
    Item* novo1 = (Item*)calloc(this->max,sizeof(Item)*this->max);
    string* novo2 = (string*)calloc(this->max, sizeof(string)*this->max);
    
    for(int i=0; i < this->qntPalavras; i++){
        novo1[i] = this->itens[i];
        novo2[i] = this->palavras[i];
    }
    
    this->itens = novo1;
    this->palavras = novo2;
}

int VO:: getQntPalavras(){
    return this->qntPalavras;
}

void VO:: insere(string key, Item val){
    int flag=0;
    int inicio, fim;
    int meio;

    inicio = 0;
    meio = 0;
    fim = this->qntPalavras-1;

    while(inicio <= fim){
        meio = (inicio + fim) / 2;

        if(strcmp(this->palavras[meio].c_str(), key.c_str()) == 0){
            this->itens[meio].qntOcorrencias += 1;
            flag=1;
            break;
        }
        
        if(strcmp(this->palavras[meio].c_str(), key.c_str()) > 0)
            fim = meio-1;
        else 
            inicio = meio+1;
    }

    if(!flag){

        if(this->qntPalavras != 0 && this->qntPalavras >= meio && strcmp(this->palavras[meio].c_str(), key.c_str()) < 0)
            meio++;

        for(int i=this->qntPalavras; i>meio; i--){
            this->palavras[i] = this->palavras[i-1];
            this->itens[i] = this->itens[i-1];
        }
        
        this->palavras[meio] = key;
        this->itens[meio] = val;
        this->qntPalavras += 1;

        if(this->max == this->qntPalavras)
            resize();
    }

    //imprime();
    //cout << "----------------" << endl; 
}

Item VO:: busca(string key){
    int inicio = 0, fim = this->qntPalavras - 1;

    // busca binária
    while(inicio <= fim){
        int meio = (inicio + fim) / 2;

        if(strcmp(this->palavras[meio].c_str(), key.c_str()) == 0)
            return this->itens[meio];

        if(strcmp(this->palavras[meio].c_str(), key.c_str()) > 0)
            fim = meio - 1;
        
        if(strcmp(this->palavras[meio].c_str(), key.c_str()) < 0)
            inicio = meio + 1;
    }

    // se não está na tabela de símbolos
    Item aux;
    aux.nVogais=0;
    aux.qntOcorrencias=0;
    aux.tam=0;
    return aux;
}

void VO:: add(string key, Item val){

    this->insere(key, val);
}

void VO:: inorder(){
    //cout << this->qntPalavras << endl;
    
    for(int i=0; i< this->qntPalavras; i++){
        cout << this->palavras[i] << " " << this->itens[i].qntOcorrencias << " " << this->itens[i].nVogais << " " << this->itens[i].tam << endl;
        //cout << this->palavras[i].palavra << endl;
    }
}

void VO:: imprime(){
    inorder();
}

void VO:: ajudaPalavrasFrequentes(pFrequentesVetor* pf){
    for(int i=0; i<this->qntPalavras; i++){
            if(this->itens[i].qntOcorrencias > pf->nFrequencia){
            pf->palavras.clear();
            pf->palavras.push_back(this->palavras[i]);
            pf->nFrequencia = this->itens[i].qntOcorrencias;
        }
        else if(this->itens[i].qntOcorrencias == pf->nFrequencia){
            pf->palavras.push_back(this->palavras[i]);
        }
    }
}
