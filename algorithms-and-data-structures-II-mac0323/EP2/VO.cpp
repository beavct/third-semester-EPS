#include <iostream>
#include <string.h>
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

void VO:: insere(string key, Item val){

    if(this->qntPalavras+1 == this->max)
        resize();

    this->palavras[this->qntPalavras].palavra = key;
    this->palavras[this->qntPalavras].item = val;
    this->qntPalavras++;

}

void VO:: quickSort(int ini, int fim){
    // base case
    if (ini >= fim)
        return;
 
    // partitioning the array
    int p = particiona(ini, fim);
 
    // Sorting the left part
    quickSort(ini, p - 1);
 
    // Sorting the right part
    quickSort(p + 1, fim);
}

int VO:: particiona(int ini, int fim){
     
    Palavras pivot = this->palavras[ini];
 
    int count = 0;
    for (int i = ini + 1; i <= fim; i++) {
        if (strcmp(this->palavras[i].palavra.c_str(), pivot.palavra.c_str()) < 0)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = ini + count;
    swap(this->palavras[pivotIndex], this->palavras[ini]);
 
    // Sorting left and right parts of the pivot element
    int i = ini, j = fim;
 
    while (i < pivotIndex && j > pivotIndex) {
        
 
        while (strcmp(this->palavras[i].palavra.c_str(), pivot.palavra.c_str()) < 0) {
            i++;
        }
 
        while (strcmp(this->palavras[j].palavra.c_str(), pivot.palavra.c_str()) > 0) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(this->palavras[i++], this->palavras[j--]);
        }
    }
 
    return pivotIndex;
}

Item VO:: busca(string key){
    int inicio = 0, fim = this->qntPalavras - 1;

    // busca binária
    while(inicio <= fim){
        int meio = (inicio + fim) / 2;

        if(strcmp(this->palavras[meio].palavra.c_str(), key.c_str()) == 0)
            return this->palavras[meio].item;

        if(strcmp(this->palavras[meio].palavra.c_str(), key.c_str()) > 0)
            fim = meio - 1;
        
        if(strcmp(this->palavras[meio].palavra.c_str(), key.c_str()) < 0)
            inicio = meio + 1;
    }

    /*for(int i = 0; i < this->qntPalavras; i++){
        if(this->palavras[i].palavra == key){
            return this->palavras[i].item;
        }
    }*/

    // se não está na tabela de símbolos
    Item aux;
    aux.nVogais=-1;
    aux.qntOcorrencias=-1;
    aux.tam=-1;
    return aux;
}

void VO:: add(string key, Item val){
    this->insere(key, val);
}

void VO:: inorder(){
    cout << this->qntPalavras << endl;
    
    for(int i=0; i< this->qntPalavras; i++)
        cout << this->palavras[i].palavra << endl;
}

