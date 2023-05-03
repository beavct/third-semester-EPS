#include "priorityQueue.h"
#include "plane.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

#define MAX 255

using namespace std;

PriorityQueue:: PriorityQueue(){
    this->flights = (Item*)malloc(MAX*sizeof(Item));
    this->n = 0;
    this->max = MAX;
    this->divertedFlights = 0;
    this->attendedArrivals = 0;
    this->attendedTakeOffs = 0;
    this->totalArrivals = 0;
    this->totalTakeOffs = 0;
}

PriorityQueue:: ~PriorityQueue(){
    free(this->flights);
}

int PriorityQueue:: emptyPriorityQueue(){
    return (this->n==0);
}

void PriorityQueue:: resizePriorityQueue(){
    this->max = this->max * 2;
    this->flights = (Item*)realloc(this->flights, this->max*sizeof(Item));
}

void PriorityQueue:: insertPriorityQueue(Item x){
    if(this->n == this->max)
        this->resizePriorityQueue();

    this->flights[this->n].flight = x.flight;
    this->flights[this->n].prior = x.prior;

    if(x.flight->getAction())
        this->totalArrivals++;
    else    
        this->totalTakeOffs++;

    upgrade(this->n);

    this->n++;
}

Item PriorityQueue:: removePriorityQueue(int i){
    Item aux;
    aux.prior = -1;
    if(!this->emptyPriorityQueue() && this->flights[i].prior != -1){
        aux = this->flights[i];
        this->n -= 1;
        this->flights[i] = this->flights[this->n];
        this->flights[this->n].prior = -1;
        this->flights[this->n].flight->setPrior(-1);

        if(aux.flight->getAction())
            this->attendedArrivals++;
        else
            this->attendedTakeOffs++;
    
        downgrade(i);
    }
    return aux;
}

void PriorityQueue:: upgrade(int i){
    int dad, son;
    son = i;
    dad = (i-1)/2;

    if(son >= 1 && this->flights[son].prior > this->flights[dad].prior){
        Item aux = this->flights[dad];
        this->flights[dad] = this->flights[son];
        this->flights[son] = aux;

        upgrade(dad);
    }
}

void PriorityQueue:: downgrade(int i) {
    int leftSon, rightSon, dad, bigger;

    dad = i;
    leftSon = 2*i+1;
    rightSon = 2*i+2;

    bigger = i;

    if(leftSon < this->n && this->flights[leftSon].prior > this->flights[bigger].prior)
        bigger = leftSon;

    if(rightSon < this->n && this->flights[rightSon].prior > this->flights[bigger].prior)
        bigger = rightSon;

    if(bigger != dad){ // troca
        Item aux = this->flights[bigger];
        this->flights[bigger] = this->flights[dad];
        this->flights[dad] = aux;

        downgrade(bigger);
    }
}

void PriorityQueue:: changePriority(int C, int V){
    int aux;

    for (int i = 0; i < this->n; i++){

        aux = this->flights[i].flight->getTimeWaiting();
        this->flights[i].flight->setTimeWaiting(aux+1);
        // incrementa o tempo de espera

        if(this->flights[i].flight->getAction() && this->flights[i].prior != -1){
            // é um pouso
            aux = this->flights[i].flight->getExtraInfo();
            if(aux >= 1){
                this->flights[i].flight->setExtraInfo(aux - 1);
                // decrementa o combustível
                this->flights[i].flight->setPrior(this->flights[i].prior + C - aux);
                this->flights[i].prior += C - aux;
                // aumenta prioridade de acordo com o combustível
                this->upgrade(i);
                // conserta o heap
            }
            else{
                // está com 0 de combustível -> redireciona para outro aeroporto
                this->flights[i].prior = -1;
                this->flights[i].flight->setPrior(-1);
                cout << setw(4) << setfill(' ') << "" <<"-- Voo de ID " << this->flights[i].flight->getFlyID() << " foi desviado para outro aeroporto por estar sem combustível" << endl;
                this->divertedFlights++;
                this->downgrade(i);
                // conserta o heap
            }

        }
        else if(!this->flights[i].flight->getAction() && this->flights[i].prior != -1){
            // é uma decolagem
            aux = this->flights[i].flight->getTimeWaiting();

            if(aux < this->flights[i].flight->getPerTime()){
                // ainda não ultrapassou 10% do tempo de voo
                this->flights[i].flight->setPrior(this->flights[i].prior + aux);
                this->flights[i].prior += aux;
                // aumenta a prioridade
                this->upgrade(i);
                // conserta o heap
            }
            else{ 
                // já esta esperando a mais de 10% do seu tempo de voo
                this->flights[i].prior += aux*2;
                this->flights[i].flight->setPrior(this->flights[i].prior + 2*aux);
                // aumenta a prioridade
                this->upgrade(i);
                // conserta o heap
            }
        }
    }
}

int PriorityQueue:: getN(){
    return this->n;
}

void PriorityQueue:: printFlightStatus(){

    for(int i = 0; i < this->n; i++){
        if(this->flights[i].prior != -1 && this->flights[i].flight->getPriority() != -1){
            cout << setw(20) << setfill(' ') << "" << "ID do avião: " << this->flights[i].flight->getCompanyID() << endl;
            cout << setw(20) << setfill(' ') << "" <<"ID do voo: " << this->flights[i].flight->getFlyID() << endl;
            if(this->flights[i].flight->getAction()){
                cout << setw(20) << setfill(' ') << "" <<"Ação: Pouso" << endl;
                cout << setw(20) << setfill(' ') << "" <<"Combustível restante: " << this->flights[i].flight->getExtraInfo() << endl;
            }
            else{
                cout << setw(20) << setfill(' ') << "" <<"Ação: Decolagem" << endl;
                cout << setw(20) << setfill(' ') << "" <<"Tempo estimado de voo: " << this->flights[i].flight->getExtraInfo() << endl;
            }
            cout << setw(20) << setfill(' ') << "" <<"Prioridade: " << this->flights[i].prior << endl;
            cout << setw(20) << setfill(' ') << "" <<"Tempo de espera: " << this->flights[i].flight->getTimeWaiting() << endl;
            if(this->flights[i].flight->getEmergency())
                cout << setw(20) << setfill(' ') << "" <<"É um voo de emergência!!!" << endl;
            else 
                cout << setw(20) << setfill(' ') << "" <<"Não é um voo de emergência" << endl;
            cout << setw(81) << setfill('-') << "" << endl;
        }
    }
}

Item PriorityQueue:: getItem(int i){
    return this->flights[i];
}

int PriorityQueue:: getArrivals(){
    int j = 0;
    for(int i = 0; i < this->n; i++)
        if(this->flights[i].flight->getAction())
            j++;
    
    return j;
}

int PriorityQueue:: getTakeOffs(){
    int j = 0;
    for(int i = 0; i < this->n; i++)
        if(!(this->flights[i].flight->getAction()))
            j++;
    
    return j;
}

double PriorityQueue:: fuelRate(){
    double rate = 0;

    for(int i = 0; i < this->n; i++)
        if(this->flights[i].flight->getAction())
            rate += this->flights[i].flight->getExtraInfo();

    return (double)(rate/this->n);
}

int PriorityQueue:: getDivertedFlights(){
    return this->divertedFlights;
}

int PriorityQueue:: getAttendedArrivals(){
    return this->attendedArrivals;
}

int PriorityQueue:: getAttendedTakeOffs(){
    return this->attendedTakeOffs;
}

int PriorityQueue:: getTotalArrivals(){
    return this->totalArrivals;
}

int PriorityQueue:: getTotalTakeOffs(){
    return this->totalTakeOffs;
}

double PriorityQueue:: getAvarageTimeWaitingArrivals(){
    int t = 0;

    for(int i = 0; i < this->n; i++)
        if(this->flights[i].flight->getAction())
            t += this->flights[i].flight->getTimeWaiting();

    if(this->n != 0)
        return (double)(t/this->n);
    return 0;
}

double PriorityQueue:: getAvarageTimeWaitingTakeOffs(){
    int t = 0;

    for(int i = 0; i < this->n; i++)
        if(!this->flights[i].flight->getAction())
            t += this->flights[i].flight->getTimeWaiting();

    if(this->n != 0)
        return (double)(t/this->n);
    return 0;
}