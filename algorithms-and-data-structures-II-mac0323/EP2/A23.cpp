#include <iostream>
#include <string.h>
#include <vector>
#include "no.h"
#include "A23.h"

using namespace std;

A23:: A23(){
    this->tam=0;
    this->raiz = nullptr; // pode ser nullptr
}

A23:: ~A23(){
    daFree(this->raiz);
}

void A23:: daFree(NoA23* raiz){
    if(raiz->esq != nullptr)
        daFree(raiz->esq);

    if(raiz->meio != nullptr)
        daFree(raiz->meio);
    
    if(raiz->dir != nullptr)
        daFree(raiz->dir);

    delete(raiz);
}

NoA23* A23:: getRaiz(){
    return this->raiz;
}

NoA23* A23:: criaNo(string key, Item item){
    NoA23* z = new NoA23();

    z->palavra1 = key;
    z->item1 = item;
    z->dir=z->esq=z->meio = nullptr;
    z->tresNo = false;
            
    return z;
}

void A23:: add(string key, Item val){
    bool cresceu = false;
    insereA23(this->raiz, key, val, &cresceu);
}

int A23:: ehFolha(NoA23* raiz){
    return (raiz->esq == nullptr && raiz->dir == nullptr && raiz->meio == nullptr);
}

NoA23* A23:: insereA23(NoA23* raiz, string key, Item item, bool* cresceu){
    
    // árvore vazia
    if(raiz == nullptr){
        raiz = new NoA23();
        raiz->palavra1 = key;
        raiz->item1 = item;
        raiz->esq = raiz->dir = raiz->meio = nullptr;
        raiz->tresNo = false;
        *cresceu = true;

        // verificar se tem que fazer essa comparação ou se pode só colocar que é a raiz
        if(this->tam == 0) 
            this->raiz = raiz;

        this->tam++;
        return raiz;
    } 

    // se é uma folha pode inserir
    if(ehFolha(raiz)){

        // se a palavra já está no nó
        // palavra1 == key  
        if(strcmp(raiz->palavra1.c_str(), key.c_str()) == 0){
            raiz->item1.qntOcorrencias++;
            *cresceu = false;
            return raiz;
        }

        // palavra2 == key
        if(raiz->tresNo)
            if(strcmp(raiz->palavra2.c_str(), key.c_str()) == 0){
                raiz->item2.qntOcorrencias++;
                *cresceu = false;
                return raiz;
            }

        // a raiz só tem uma palavra, então podemos encaixar a key
        if(!(raiz->tresNo)){
            if(strcmp(raiz->palavra1.c_str(), key.c_str()) < 0){
                raiz->palavra2 = key;
                raiz->item2 = item;
                this->tam++;
            }

            else{
                raiz->palavra2 = key;
                raiz->item2 = item;
                this->tam++;
            }

            raiz->tresNo = true;
            *cresceu = false;

            return raiz;
        }

        else{ // nossa raiz já possui duas palavras
            // adiciona à esquerda
            // key < palavra1 < palavra2
            if(strcmp(raiz->palavra1.c_str(), key.c_str()) > 0){
                NoA23* maior = criaNo(raiz->palavra2, raiz->item2);
                NoA23* meio = criaNo(raiz->palavra1, raiz->item1);

                raiz->palavra1 = key;
                raiz->palavra2 = nullptr;
                raiz->tresNo = false;

                meio->meio = maior;
                meio->esq = raiz;

                *cresceu = true;
                this->tam++;

                return meio;
            }
            // adicionar no centro
            // palavra1 < key < palavra2
            if(strcmp(raiz->palavra2.c_str(), key.c_str()) > 0){
                NoA23* maior = criaNo(raiz->palavra2, raiz->item2);
                NoA23* meio = criaNo(key, item);

                raiz->palavra2 = nullptr;
                raiz->tresNo = false;

                meio->esq = raiz;
                meio->meio = maior;

                *cresceu = true;
                this->tam++;

                return meio;
            }

            // adiciona à direita
            // palavra1 < palavra2 < key
            else{
                NoA23* meio = criaNo(raiz->palavra2, raiz->item2);
                NoA23* maior = criaNo(key, item);

                raiz->palavra2 = nullptr;
                raiz->tresNo = false;

                meio->esq = raiz;
                meio->meio = maior;

                *cresceu = true;
                this->tam++;
                
                return meio;
            }

        }
        
    }

    // não é folha
    else{ 

        // key < palavra1 < palavra2 -> insere na esquerda
        if(strcmp(raiz->palavra1.c_str(), key.c_str()) > 0){
            NoA23* aux = insereA23(raiz->esq, key, item, cresceu);

            if(!*cresceu){
                raiz->esq = aux;
                delete(aux);
                return raiz;
            }
            else{
                // a raiz tem apenas uma chave, então dá para encaixar outra 
                if(!raiz->tresNo){
                    raiz->palavra2 = raiz->palavra1;
                    raiz->item2 = raiz->item1;

                    raiz->palavra1 = aux->palavra1;
                    raiz->item1 = aux->item1;

                    raiz->dir = raiz->meio;
                    raiz->meio = aux->meio;
                    raiz->esq = aux->esq;


                    delete(aux);
                    return raiz;
                }
                else{
                    NoA23* menor = aux;
                    NoA23* maior = criaNo(raiz->palavra2, raiz->item2);

                    maior->esq = raiz->meio;
                    maior->meio = raiz->dir;

                    raiz->palavra2 = nullptr;
                    raiz->tresNo = false;
                    raiz->esq = menor;
                    raiz->meio = maior;
                    raiz->dir = nullptr;
                    *cresceu = true;


                    return raiz;

                }
            }


        }

        else{
            // palavra1 < key
            if(!raiz->tresNo){
                NoA23* aux = insereA23(raiz->meio, key, item, cresceu);

                if(!*cresceu){
                    raiz->meio = aux;
                    raiz->dir = aux;
                }
                else{
                    raiz->palavra2 = aux->palavra1;
                    raiz->item2 = aux->item1;
                    raiz->tresNo = true;

                    raiz->dir = aux->meio;
                    raiz->meio = aux->esq;

                    *cresceu = false;
                    delete(aux);

                    return raiz;
                }

            }
            else{
                // a raiz já tem duas chaves
                // palavra1 < pavra2 < key
                if(strcmp(raiz->palavra2.c_str(), key.c_str()) < 0){
                    NoA23* aux = insereA23(raiz->dir, key, item, cresceu);

                    if(!*cresceu){
                        raiz->dir = aux;
                        return raiz;
                    }
                    else{
                        // cresceu é true
                        NoA23* maior = aux;
                        NoA23* meio = criaNo(raiz->palavra2, raiz->item2);

                        raiz->palavra2 = nullptr;
                        raiz->dir = nullptr;
                        raiz->tresNo = false;

                        meio->esq = raiz;
                        meio->meio = maior;

                        *cresceu=true;

                        delete(aux);

                        return meio;
                    }
                }

                else{
                    // palavra1 < key < palavra2
                    NoA23* aux = insereA23(raiz->meio, key, item, cresceu);

                    if(!*cresceu){
                        raiz->meio = aux;
                        delete(aux);
                        return raiz;
                    }
                    else{
                        NoA23* meio = aux;
                        NoA23* maior = criaNo(raiz->palavra2, raiz->item2);
                        delete(aux);

                        maior->meio = raiz->dir;
                        maior->esq = meio->meio;

                        raiz->palavra2 = nullptr;
                        raiz->dir = nullptr;
                        raiz->tresNo = false;
                        raiz->meio = meio->esq;

                        meio->esq = raiz;
                        meio->meio = maior;

                        *cresceu=true;
                        return meio;
                    }
                }
            }
        }
    }
    return raiz; // só pro compilador n chorar
}

Item A23:: buscaA23(NoA23* raiz, string key){
    
    // acho que ta certo
    const char* aux1 = key.c_str();
    const char* aux2 = raiz->palavra1.c_str();
    const char* aux3 = raiz->palavra2.c_str();

    if(raiz == nullptr){
        // se não está na tabela de símbolos
        Item aux;
        aux.nVogais=0;
        aux.qntOcorrencias=0;
        aux.tam=0;
        return aux;
    }

    if(strcmp(aux1, aux2) == 0 )
        return raiz->item1;
    
    
    if((raiz->tresNo) && strcmp(aux1, aux3) == 0)
        return raiz->item2;
    

    if(strcmp(aux1, aux2) < 0)
        return buscaA23(raiz->esq, key);

    if(raiz->tresNo && strcmp(aux1, aux2) < 0 && strcmp(aux1, aux3) > 0)
        return buscaA23(raiz->meio, key);

    return buscaA23(raiz->dir, key);
}

void A23:: viz(NoA23* node)
{
    if (node == nullptr)
    {
        return;
    }

    std::cout << node->palavra1 << "[label=\"" << node->palavra1;

    if (!node->tresNo)
    {
        std::cout << " " << node->palavra2;
    }

    std::cout << "\"];\n\n";

    if (node->esq != nullptr)
    {
        std::cout << node->palavra1 << " -> " << node->esq->palavra1 << "\n";
        std::cout << node->palavra1 << " -> " << node->meio->palavra1 << "\n";
    }
    if (node->dir != nullptr)
    {
        std::cout << node->palavra1 << " -> " << node->dir->palavra1 << "\n";
    }

    viz(node->esq);
    viz(node->meio);
    viz(node->dir);
}

void A23::inorder(NoA23* raiz){
    // acho que ta certo
    //if(raiz->esq != nullptr)
    //    inorder(raiz->esq);

    //cout << (raiz==nullptr) << endl;
    cout << raiz->palavra1 << endl;

    //if(raiz->tresNo) {
    //    if(raiz->meio != nullptr)
    //        inorder(raiz->meio);
    //    cout << raiz->palavra2 << endl;
    //}

    //if(raiz->dir != nullptr)
    //    inorder(raiz->dir);

}

void A23:: imprime(){
    this->inorder(this->raiz);
}

Item A23:: busca(string key){
    return this->buscaA23(this->raiz, key);
}

vector<string> palavrasFrequentes(){
    
}