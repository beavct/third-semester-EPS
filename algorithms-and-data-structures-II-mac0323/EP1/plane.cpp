#include "plane.h"
#include "randomGenerator.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Plane:: Plane(double Pp, double Pd, double Pe, int C, int V, int i){
    this->companyID = (char*)malloc(6*sizeof(char*));
    this->flyID = (char*)malloc(4*sizeof(char*));
    this->timeWaiting = 0;

    RandomGenerator testPlane(C+V+i+time(NULL));

    this->action = testPlane.genarateAction(Pp, Pd);
    this->companyID = testPlane.genarateCompanyID();
    this->flyID = testPlane.generateFlyID(); 
    this->emergency = testPlane.generateEmergency(Pe);

    if(this->action == 1){ // pouso 
        this->extraInfo = testPlane.genarateFuel(C);
        this->perTime = -1;
    }
    else{ // decolagem
        this->extraInfo = testPlane.genarateEstimatedTime(V); 
        this->perTime = this->extraInfo * 0.1;
    }

    this->priority = 1;
}

Plane:: ~Plane(){
    free(this->companyID);
    free(this->flyID);
    free(this);
}

char* Plane:: getCompanyID(){
    return companyID;
}

char* Plane:: getFlyID(){
    return flyID;
}

int Plane:: getEmergency(){
    return emergency;
}

int Plane:: getExtraInfo(){
    return extraInfo;
}

int Plane:: getAction(){
    return action;
}

int Plane:: getTimeWaiting(){
    return timeWaiting;
}

double Plane:: getPerTime(){
    return perTime;
}

int Plane:: getPriority(){
    return this->priority;
}

void Plane:: setExtraInfo(int x){
    this->extraInfo = x;
}

void Plane:: setTimeWaiting(int x){
    this->timeWaiting = x;
}

void Plane:: setPrior(int i){
    this->priority = i;
}