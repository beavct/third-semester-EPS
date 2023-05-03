#pragma once
#include "plane.h"

using namespace std;

typedef struct{
    Plane *flight;
    int prior;
}Item;


class PriorityQueue{
    protected:
        Item* flights; // armazena o heap
        int n; // número de elementos na fila (heap)
        int max; // tamanho da fila
        int divertedFlights; // voos que queria pousas e foram desviados;
        int attendedArrivals;
        int attendedTakeOffs;
        int totalArrivals;
        int totalTakeOffs;
    public:
        PriorityQueue();
        ~PriorityQueue();
        void resizePriorityQueue();
        int emptyPriorityQueue();
        Item removePriorityQueue(int i);
        void insertPriorityQueue(Item x);
        void upgrade(int i);
        void downgrade(int i);
        void changePriority(int C, int V);
        int getN();
        void printFlightStatus();
        int getArrivals();
        int getTakeOffs();
        Item getItem(int i);
        double fuelRate();
        int getDivertedFlights();
        int getAttendedArrivals();
        int getAttendedTakeOffs();
        int getTotalArrivals();
        int getTotalTakeOffs();
        double getAvarageTimeWaitingArrivals();
        double getAvarageTimeWaitingTakeOffs();
};