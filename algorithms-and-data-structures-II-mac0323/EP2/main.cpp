#include <bits/stdc++.h>
#include "no.h"
#include "VO.h" // a estrutura básica ta ok
#include "ABB.h" // a estrutura básica ta ok
#include "TR.h" // a estrutura básica ta ok
#include "ARN.h"
#include "A23.h"

using namespace std;

// taok
int repeteLetra(string palavra){
    char vetorAux[26];
    int i = 0;

    for(int j=0; j<strlen(palavra.c_str()); j++){

        for(int k =0; k<i; k++){
            if(palavra[j] == vetorAux[k])
                return 0; // repetiu letras
        }

        vetorAux[i++] = palavra[j];
        
    }

    return 1; // não repetiu letras
}

string* resize(string* vetor, int x){
    x *= 2;
    return ((string*)realloc(vetor, sizeof(string) * x));
}

int contaVogais(string s){
    int Af, Ef, If, Of, Uf;
    int j=0;
    Af=Ef=If=Of=Uf=0;

    for(int i=0; i<(int)strlen(s.c_str()) && j!=5; i++){

        if(Af==0 && (s[i] == 'A' || s[i] == 'a')){
            Af=1;
            j++;
        }

        if(Ef==0 && (s[i] == 'E' || s[i] == 'e')){
            Ef=1;
            j++;
        }

        if(If==0 && (s[i] == 'I' || s[i] == 'i')){
            If=1;
            j++;
        }

        if(Of==0 && (s[i] == 'O' || s[i] == 'o')){
            Of=1;
            j++;
        }

        if(Uf==0 && (s[i] == 'U' || s[i] == 'u')){
            Uf=1;
            j++;
        }

    }

    return j;
}

int main(){
    // instância as estrututas
    VO *vetorOrdenado =  new VO();
    ABB *arvoreBB = new ABB();
    TR *treap = new TR();
    ARN *arvoreRN = new ARN();
    A23 *arvore23 = new A23();

    // vetores que guardarão as infos que podem ser consultadas
    string *pFrequentes; // palavras mais frequentes do texto -> vou ter que olhar as estruturas mesmo
    string *pLongas; // palavras mais longas -> pré-processamento
    string *maioresSemRepeticao; // n repetem letras
    string *menoresComMaisVogais; // vogais sem repetição

    // variáveis que guardam os valores 
    int numFrequentes, quantFrequentes;
    int tamLongas = 0, quantLongas = 0;
    int tamMaiores, quantMaiores, quantVogais;


    // variáveis que serão utilizadas na leitura
    int nPalavras, nConsultas;
    fstream file;
    string nomeArq, estrut, palavra, consulta;

    // símbolos que serão descartados 
    string  remover = "'!@#$%*()+=§[]{}|<>,.:;?/"; 


    // LEITURA DO ARQUIVO
    cout << "Digite o nome do arquivo de entrada: ";
    cin >> nomeArq;

    file.open(nomeArq.c_str());

    file >> estrut;
    file >> nPalavras;


    // leitura e limpeza das palavras está ok
    for(int i = 0; i<nPalavras; i++){
        string palavra;
        Item auxItem;

        file >> palavra;

        for(char c: remover)
            palavra.erase(remove(palavra.begin(), palavra.end(), c), palavra.end());

        auxItem.tam = (int)strlen(palavra.c_str());
        auxItem.qntOcorrencias = 1;
        auxItem.nVogais = contaVogais(palavra);

        // insere na estrutura correta
        if(estrut == "VO")
            vetorOrdenado->add(palavra, auxItem);
        else if(estrut == "ABB")
            arvoreBB->add(palavra, auxItem);
        else if(estrut == "TR")
            treap->add(palavra, auxItem);
        else if(estrut == "ARN")
            arvoreRN->add(palavra, auxItem);
        else // A23
            arvore23->add(palavra, auxItem);

        //cout << "palavra: " << palavra << endl << " letras sem repetição: " << repeteLetra(palavra) << endl;
    }

    file >> nConsultas;
    string consultas[nConsultas];

    //if(estrut == "TR")
    //    treap->inorder(treap->getRaiz());

    // lê as consultas desejadas
    for(int i=0; i<nConsultas; i++){
        file >> consultas[i];
    }
    file.close();

    for(int i=0; i<nConsultas; i++){
        cout << consultas[i];
    }

    return 0;
}