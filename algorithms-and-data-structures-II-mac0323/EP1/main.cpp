#include <iostream>
#include <iomanip>
#include <random>

#include "file.h"
#include "plane.h"
#include "randomGenerator.h"
#include "priorityQueue.h"
#include "runway.h"

// variáveis globais para o cálculo das estatísticas
int FUEL = 0;
int TIME_ARRIVAL = 0;
int TIME_TAKEOFF = 0;
int QUANT_ARRIVAL = 0; 
int QUANT_TAKEOFF = 0;
int QUANT_ARRIVAL_EMERG = 0;
int QUANT_TAKEOFF_EMERG = 0;

using namespace std;

// gera o avião e o insere em sua respectiva fila
void generatePlanes(PriorityQueue *normal, PriorityQueue *emergencyArrival, PriorityQueue *emergencyTakeOff, int i, int K, double Pp, double Pd, double Pe, int C, int V, int j){
    Item newPlane;
    newPlane.flight = new Plane(Pp, Pd, Pe, C, V, C+V+j+time(NULL));

    newPlane.prior = newPlane.flight->getPriority();

    if(newPlane.flight->getAction() && newPlane.flight->getEmergency() == 1){
        // é um voo de emergência e pouso
        emergencyArrival->insertPriorityQueue(newPlane);
    }

    else if(!newPlane.flight->getAction() && newPlane.flight->getEmergency() == 1){
        // é um voo de emergência e decolagem
        emergencyTakeOff->insertPriorityQueue(newPlane);
    }
    else{
        // não é um voo de emergência
        normal->insertPriorityQueue(newPlane);
    }
}

// lê o arquivo de entrada
void getInput(File file, int* T, int* K, double* Pp, double* Pd, double* Pe, int* C, int* V){
    file.readFile();
    *T = file.getT();
    *K = file.getK();
    *Pp = file.getPd();
    *Pe = file.getPe();
    *C = file.getC();
    *V = file.getV();
}

// printa a saída do avião da fila e para qual pista ele foi mandado
void printArrivalTakeoff(Item aux, int i){
    if(aux.prior != -1){
        int action = aux.flight->getAction();

        if(action){
            cout << setw(18) << setfill(' ') << "" << ">> Voo de ID " << aux.flight->getFlyID() << " pousou na pista " << i << endl;
            TIME_ARRIVAL += aux.flight->getTimeWaiting();
            FUEL += aux.flight->getExtraInfo();
            QUANT_ARRIVAL+=1;
        }
        else{
            cout << setw(18) << setfill(' ') << "" << ">> Voo de ID " << aux.flight->getFlyID() << " decolou na pista "<< i << endl;
            TIME_TAKEOFF += aux.flight->getTimeWaiting();
            QUANT_TAKEOFF+=1;
        }
    }
}

// manda os aviões para as torres
void controlTower(PriorityQueue *normal, PriorityQueue *emergencyArrival, PriorityQueue *emergencyTakeOff, Runway *firstRunway, Runway *secondRunway, Runway *thirdRunway){
    int normalN, emergencyAN, emergencyTN;
    Item aux;

    // guardamos quantos aviões tem em cada fila
    normalN = normal->getN();
    emergencyAN = emergencyArrival->getN();
    emergencyTN = emergencyTakeOff->getN();

    // cuidamos da pista 1
    if(firstRunway->getCoolDown() <= 0){
    // se a pista 1 já pode receber aviões

        if(emergencyAN != 0 || emergencyTN != 0){
        // vamos dar preferência para a emergência
            if(emergencyAN >= emergencyTN && emergencyAN > normalN){
                aux = emergencyArrival->removePriorityQueue(0);
                firstRunway->addCoolDown();
                emergencyAN--;
                printArrivalTakeoff(aux, 1);
            }
            else if(emergencyTN > normalN){
                aux = emergencyTakeOff->removePriorityQueue(0);
                firstRunway->addCoolDown();
                emergencyTN--;
                printArrivalTakeoff(aux, 1);
            }
        }
        if(normalN > 0 && firstRunway->getCoolDown() <= 0){
            aux = normal->removePriorityQueue(0);
            firstRunway->addCoolDown();
            normalN--;
            printArrivalTakeoff(aux, 1);
        }
    }
    
    // pista 2
    if(secondRunway->getCoolDown() <= 0){

        if(emergencyAN != 0 || emergencyTN != 0){
        // vamos dar preferência para a emergência
            if(emergencyTN >= emergencyAN && emergencyTN > normalN){
                aux = emergencyTakeOff->removePriorityQueue(0);
                secondRunway->addCoolDown();
                emergencyTN--;
                printArrivalTakeoff(aux, 2);
            }
            else if(emergencyAN > normalN){
                aux = emergencyArrival->removePriorityQueue(0);
                secondRunway->addCoolDown();
                emergencyAN--;
                printArrivalTakeoff(aux, 2);
            }
        }
        if(normalN > 0 && secondRunway->getCoolDown() <= 0){
            aux = normal->removePriorityQueue(0);
            secondRunway->addCoolDown();
            normalN--;
            printArrivalTakeoff(aux, 2);
        }
    }

    // pista 3
    if(thirdRunway->getCoolDown() <= 0){

        if(emergencyAN != 0){
            aux = emergencyArrival->removePriorityQueue(0);
            thirdRunway->addCoolDown();
            emergencyAN--;
            printArrivalTakeoff(aux, 3);
        }
        else if(emergencyTN != 0){
            aux = emergencyTakeOff->removePriorityQueue(0);
            thirdRunway->addCoolDown();
            emergencyAN--;
            printArrivalTakeoff(aux, 3);
        }
        else if(normalN != 0){
            int i = 0;
            aux = normal->getItem(i);
            while(aux.flight->getAction() && i < normal->getN()){
                i++;
                aux = normal->getItem(i);
            }
            if(!aux.flight->getAction()){
                aux = normal->removePriorityQueue(i);
                thirdRunway->addCoolDown();
                normalN--;
                printArrivalTakeoff(aux, 3);
            }
        }
    }
}

// decrenta o cool down das pistas
void uploadRunways(Runway *firstRunway, Runway *secondRunway, Runway *thirdRunway){
    firstRunway->subCoolDown();
    secondRunway->subCoolDown();
    thirdRunway->subCoolDown();
}

int main(){
    // cria filas de prioridade
    PriorityQueue *normal = new PriorityQueue();
    PriorityQueue *emergencyArrival = new PriorityQueue();
    PriorityQueue *emergencyTakeOff = new PriorityQueue();

    // cria pistas
    Runway *firstRunway = new Runway();
    Runway *secondRunway = new Runway();
    Runway *thirdRunway = new Runway();

    // instância objeto para leitura do arquivo
    File file;

    int T, K, C, V;
    double Pp, Pd, Pe;
    int TOTAL_PLANES = 0;

    // iteradores
    int i, j;

    // lê o arquivo de entrada
    getInput(file, &T, &K, &Pp, &Pd, &Pe, &C, &V);
    
    for(i = 0; i < T; i++){
        
        cout << endl;
        cout << setw(81) << setfill('-') << "" << endl;
        cout << setw(49) << setfill(' ') << "UNIDADE DE TEMPO: " << i+1 << endl;
        cout << setw(81) << setfill('-') << "" << endl;

        srand(time(0)+i*i*i);
        int l = rand() % (K+1);
        TOTAL_PLANES += l;
        for(j = 0; j < l; j++){
 
            // gera os aviões
            generatePlanes(normal, emergencyArrival, emergencyTakeOff, T, K, Pp, Pd, Pe, C, V, i+j+time(0));

        }
        cout << setw(49) <<setfill(' ') << "AVIÕES GERADOS: "<< l << endl;
        cout << setw(81) << setfill('-') << "" << endl;

        cout << setw(51) << setfill(' ') << "STATUS DO AEROPORTO:" << endl;
        cout << setw(81) << setfill('-') << "" << endl;
        cout << setw(47) << setfill(' ') << "VOOS NORMAIS:" << endl;
        cout << setw(13) << setfill(' ') << "" <<"* Pousos: " << normal->getArrivals() << endl;
        cout << setw(13) << setfill(' ') << "" << "* Decolagens: " << normal->getTakeOffs() << endl;
        cout << setw(13) << setfill(' ') << "" << "* Quant. média de combustível dos aviões na fila de pouso: " << fixed << setprecision(2) << normal->fuelRate() << endl;
        cout << setw(13) << setfill(' ') << "" << "* Tempo médio de espera dos aviões na fila de pouso: " << fixed << setprecision(2) << normal->getAvarageTimeWaitingArrivals() << endl;
        cout << setw(13) << setfill(' ') << "" << "* Tempo médio de espera dos aviões na fila de decolagem: " << fixed << setprecision(2) << normal->getAvarageTimeWaitingTakeOffs() << endl;
        cout << setw(81) << setfill('-') << "" << endl;
        cout << setw(49) << setfill(' ') << "VOOS DE EMERGÊNCIA:" << endl;
        cout << setw(13) << setfill(' ') << "" << "* Pousos: " << emergencyArrival->getN() << endl;
        cout << setw(13) << setfill(' ') << "" << "* Decolagens: " << emergencyTakeOff->getN() << endl;
        cout << setw(13) << setfill(' ') << "" << "* Quant. média de combustível dos aviões na fila de pouso: " << fixed << setprecision(2) << emergencyArrival->fuelRate() << endl;
        cout << setw(13) << setfill(' ') << "" << "* Tempo médio de espera dos aviões na fila de pouso: " << fixed << setprecision(2) << emergencyArrival->getAvarageTimeWaitingArrivals() << endl;
        cout << setw(13) << setfill(' ') << "" << "* Tempo médio de espera dos aviões na fila de decolagem: " << fixed << setprecision(2) << emergencyTakeOff->getAvarageTimeWaitingTakeOffs() << endl;
        cout << setw(81) << setfill('-') << "" << endl;

        normal->printFlightStatus();
        emergencyArrival->printFlightStatus();
        emergencyTakeOff->printFlightStatus();

        controlTower(normal, emergencyArrival, emergencyTakeOff, firstRunway, secondRunway, thirdRunway);

        normal->changePriority(C, V);
        emergencyArrival->changePriority(C, V);
        emergencyTakeOff->changePriority(C, V);
        uploadRunways(firstRunway, secondRunway, thirdRunway);
        cout << setw(81) << setfill('-') << "" << endl;
        cout << endl;
    }

    double TM_ARRIVAL = 0, TM_TAKEOFF = 0, FM_ARRIVAL = 0;

    if(QUANT_ARRIVAL != 0){
        TM_ARRIVAL = ((double)TIME_ARRIVAL/QUANT_ARRIVAL);
        FM_ARRIVAL = ((double)FUEL/QUANT_ARRIVAL);
    }
    if(QUANT_TAKEOFF != 0)
        TM_TAKEOFF = ((double)TIME_TAKEOFF/QUANT_TAKEOFF);

    cout << setw(51) << setfill(' ') << "ESTATÍSTICAS DA SIMULAÇÃO:" << endl;
    cout << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Quatidade total de aviões gerados: " << TOTAL_PLANES << endl;
    cout << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Tempo médio de espera para pousar: " << fixed << setprecision(2) << (double)TM_ARRIVAL << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Quant. média de combustível dos aviões que pousaram: " << fixed << setprecision(2) << (double)FM_ARRIVAL << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Quantidade total de pousos solicitados: " << (normal->getArrivals()+emergencyArrival->getArrivals()) << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Quantidade de pousos normais atendidos: " << normal->getAttendedArrivals() << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Quantidade de pousos de emergência atendidos: " << emergencyArrival->getAttendedArrivals() << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Quantidade de pousos desviados: " << (normal->getDivertedFlights()+emergencyTakeOff->getDivertedFlights()) << endl;
    cout << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Tempo médio de espera para decolar: "  << fixed << setprecision(2) << (double)TM_TAKEOFF << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Quantidade total de decolagens solicitadas: " << (normal->getTotalTakeOffs()+emergencyTakeOff->getTotalTakeOffs()) << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Quantidade de decolagens normais atendidas: " << normal->getAttendedTakeOffs() << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Quantidade de decolagens de emergência atendidas: " << emergencyTakeOff->getAttendedTakeOffs() << endl;
    cout << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Quantidade total de voos de emergência: "  << (emergencyArrival->getTotalArrivals()+emergencyTakeOff->getTotalTakeOffs()) << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Quantidade de voos de emergência atendidos: "  << (emergencyArrival->getAttendedArrivals()+emergencyTakeOff->getAttendedTakeOffs()) << endl;
    cout << endl;
    cout << setw(13) << setfill(' ') << "" <<"* Total de voos atendidos: "  << (emergencyArrival->getAttendedArrivals()+emergencyTakeOff->getAttendedTakeOffs()+normal->getAttendedArrivals()+normal->getAttendedTakeOffs()) << endl;
    cout << setw(81) << setfill('-') << "" << endl;


    // deleta os ponteiros criados com new()
    delete(firstRunway);
    delete(secondRunway);
    delete(thirdRunway);
    
    delete(normal);
    delete(emergencyArrival);
    delete(emergencyTakeOff);


    return 0;
}