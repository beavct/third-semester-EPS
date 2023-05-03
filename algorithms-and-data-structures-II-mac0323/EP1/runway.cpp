#include "runway.h"

Runway:: Runway(){
    this->coolDown = 0;
}

Runway:: ~Runway(){

}

int Runway:: getCoolDown(){
    return this->coolDown;
}

void Runway:: addCoolDown(){
    this->coolDown = 3;
}

void Runway:: subCoolDown(){
    this->coolDown -= 1;
}