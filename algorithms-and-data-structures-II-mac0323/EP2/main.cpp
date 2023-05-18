#include <bits/stdc++.h>
#include "no.h"
#include "VO.h" // a estrutura básica ta ok
#include "ABB.h" // a estrutura básica ta ok
#include "TR.h" // a estrutura básica ta ok
#include "ARN.h"
#include "A23.h"

using namespace std;

struct vetorGenerico{
    vector<string>palavras;
    int aux1 = 0;
    int aux2 = INT_MAX; // só vai ser usado no caso das menores palavras com mais vogais sem repetição
};

// taok
int nRepeteVogal(string palavra){
    char vogais[5];
    int j=0;

    for (int i=0; i<(int)strlen(palavra.c_str()); i++){
        char aux = tolower(palavra[i]);

        if(aux == 'a' || aux == 'e' || aux == 'i' || aux == 'o' || aux == 'u'){
            for(int k=0; k<j; k++){
                if(vogais[k] == aux)
                    return 0; // repete vogal

            }
            vogais[j++] = aux;
        }
    }

    return 1; // não repete vogal
}

// taok
int nRepeteLetra(string palavra){
    char vetorAux[26];
    int i = 0;

    for(int j=0; j<(int)strlen(palavra.c_str()); j++){
        char aux = tolower(palavra[j]);

        for(int k =0; k<i; k++){
            if(aux == vetorAux[k])
                return 0; // repetiu letras
        }

        vetorAux[i++] = aux;
        
    }

    return 1; // não repetiu letras
}

// taok - só n conta palavras com acento
int contaVogais(string s){
    //int Af, Ef, If, Of, Uf;
    char vogais[5];
    int j=0, flag=0;
    //Af=Ef=If=Of=Uf=0;

    for(int i=0; i<(int)strlen(s.c_str()) && j!=5; i++){
        char aux = tolower(s[i]);

        if(aux == 'a' || aux == 'e' || aux == 'i' || aux == 'o' || aux == 'u'){
            for(int k=0; k<j; k++){
                if(vogais[k] == aux)
                    flag = 1;

            }
            if(!flag)
                vogais[j++] = aux;

            flag=0;
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
    vetorGenerico pFrequentes; // palavras mais frequentes do texto -> vou ter que olhar as estruturas mesmo
    vetorGenerico pLongas; // palavras mais longas -> pré-processamento
    vetorGenerico maioresSemRepeticao; // n repetem letras
    vetorGenerico menoresComMaisVogais; // vogais sem repetição

    // variáveis que serão utilizadas na leitura
    int nPalavras, nConsultas;
    fstream file;
    string nomeArq, estrut, palavra, consulta;

    // símbolos que serão descartados 
    string  remover = "012345678'9!@#$%*()+=§[]{}|<>,.:\";?/"; 


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

        // limpa a palavra
        for(char c: remover)
            palavra.erase(remove(palavra.begin(), palavra.end(), c), palavra.end());

        // preenche as informações da palavra
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

        // cuida do vetor de palavras mais frequentes - FUNÇÃO F
        for(int i=0; i<(int)pFrequentes.palavras.size();i++){
            if(pFrequentes.palavras[i] == palavra){
                auxItem.qntOcorrencias += pFrequentes.aux1;
                break;
            }
        }
        if(auxItem.qntOcorrencias > pFrequentes.aux1){
            pFrequentes.palavras.clear();
            pFrequentes.palavras.push_back(palavra);
            pFrequentes.aux1 = auxItem.qntOcorrencias;
        }
        else if(auxItem.qntOcorrencias == pFrequentes.aux1){
            pFrequentes.palavras.push_back(palavra);

        }

        // cuida das palavras mais longas - FUNÇÃO L
        if(auxItem.tam > pLongas.aux1){
            pLongas.palavras.clear();
            pLongas.palavras.push_back(palavra);
            pLongas.aux1 = auxItem.tam;
        }
        else if(auxItem.tam == pLongas.aux1){
            pLongas.palavras.push_back(palavra);
        }

        // cuida das maiores palavras que não repetem letras - FUNÇÃO SR
        if(auxItem.tam > maioresSemRepeticao.aux1 && nRepeteLetra(palavra)){
            maioresSemRepeticao.palavras.clear();
            maioresSemRepeticao.palavras.push_back(palavra);
            maioresSemRepeticao.aux1 = auxItem.tam;
        }
        else if(auxItem.tam == maioresSemRepeticao.aux1 && nRepeteLetra(palavra)){
            int flagMaior=1;
            for(int i=0; i<(int)maioresSemRepeticao.palavras.size();i++)
                if(maioresSemRepeticao.palavras[i] == palavra){
                    flagMaior = 0;
                    break;
                }
            if(flagMaior)
                maioresSemRepeticao.palavras.push_back(palavra);
        }


        // cuida das menores palavras com mais vogaus sem repetição - FUNÇÃO VD
        /*
        if(nRepeteVogal(palavra) && auxItem.tam < menoresComMaisVogais.aux2 && auxItem.nVogais > menoresComMaisVogais.aux1){
            cout << palavra << " entrou aq1" << endl;
            menoresComMaisVogais.palavras.clear();
            menoresComMaisVogais.palavras.push_back(palavra);
            menoresComMaisVogais.aux2 = auxItem.tam;
            menoresComMaisVogais.aux1 = auxItem.nVogais;
        }
        */
       // acho que ta certo
       if(nRepeteVogal(palavra) && auxItem.nVogais >= menoresComMaisVogais.aux1){
                menoresComMaisVogais.palavras.clear();
                menoresComMaisVogais.palavras.push_back(palavra);
                menoresComMaisVogais.aux2 = auxItem.tam;
                menoresComMaisVogais.aux1 = auxItem.nVogais;   
       }
        else if(nRepeteVogal(palavra) && auxItem.tam == menoresComMaisVogais.aux2 && auxItem.nVogais == menoresComMaisVogais.aux1){
            int flagMenor=1;
            cout << palavra << " entrou aq2" << endl;
            for(int i=0; i<(int)maioresSemRepeticao.palavras.size();i++)
                if(maioresSemRepeticao.palavras[i] == palavra){
                    flagMenor = 0;            
                    break;
                }
            if(flagMenor)
                menoresComMaisVogais.palavras.push_back(palavra);
        }
    }

    // ordenar o vetor depois da leitura
    if(estrut == "VO")
        vetorOrdenado->quickSort(0, vetorOrdenado->getQntPalavras()-1);

    file >> nConsultas;

    // lê as consultas desejadas
    for(int i=0; i<nConsultas; i++){
        file >> consulta;


        // quais as palavras mais frequêntes no texto - FUNÇÃO F
        if(consulta == "F"){
            for(int i=0; i<(int)pFrequentes.palavras.size(); i++){
                cout << pFrequentes.palavras[i] << endl;
            }
        }
        // procura a quantidade de ocorrências de uma palavra - FUNÇÃO O
        else if(consulta == "O"){
            string palavraProcurada;
            Item auxItem;
            file >> palavraProcurada;
            
            if(estrut == "VO")
                auxItem = vetorOrdenado->busca(palavraProcurada);
            else if(estrut == "ABB")
                auxItem = arvoreBB->busca(palavraProcurada);
            else if(estrut == "TR")
                auxItem = treap->busca(palavraProcurada);
            else if(estrut == "ARN")
                auxItem = arvoreRN->busca(palavraProcurada);
            else // A23
                auxItem = arvore23->busca(palavraProcurada);

            cout << auxItem.qntOcorrencias << endl;
        }
        // quais as palavras mais longas - FUNÇÃO L 
        else if(consulta == "L"){
            for(int i=0; i<(int)pLongas.palavras.size(); i++){
                cout << pLongas.palavras[i] << endl;
            }            
        }
        // quais as maiores palavras que não repetem letras - FUNÇÃO SR
        else if(consulta == "SR"){
            for(int i=0; i<(int)maioresSemRepeticao.palavras.size(); i++){
                cout << maioresSemRepeticao.palavras[i] << endl;
            }           
        }
        // quais as menores palavras com mais vogais sem repetição - FUNÇÃO VD
        else{
            for(int i=0; i<(int)menoresComMaisVogais.palavras.size(); i++){
                cout << menoresComMaisVogais.palavras[i] << endl;
            }           
        }
    }

    // imprime as palavras e frequências das estrutruturas
    /*
    if(estrut == "VO")
        vetorOrdenado->imprime();
    else if(estrut == "ABB")
        arvoreBB->imprime();
    else if(estrut == "TR")
        treap->imprime();
    else if(estrut == "ARN")
        arvoreRN->imprime();
    else // A23
        arvore23->imprime();
    */

    file.close();


    return 0;
}