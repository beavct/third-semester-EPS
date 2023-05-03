#include "file.h"
#include "randomGenerator.h"
#include <cstdlib>
#include <iostream>

using namespace std;

RandomGenerator:: RandomGenerator(int i){
    this->seed = time(NULL)+i; 
}

RandomGenerator:: ~RandomGenerator(){

}

int RandomGenerator:: genarateAction(double Pp, double Pd){
    srand(this->seed+1000*Pp);
    
    if((double)rand()/(double)RAND_MAX <= Pp)
        return 1; // Pouso
    return 0;// Decolagem
}

char* RandomGenerator:: genarateCompanyID(){
    char* companyID = (char*)malloc(6*sizeof(char));

    srand(this->seed);

    for(int i = 0; i < 2; i++)
        companyID[i] = (rand() % 10)+'0';
    for(int i = 2; i < 5; i++)
        companyID[i] = (rand() % 26) + 'A';
    companyID[5] = '\0';

    return companyID;
}

char* RandomGenerator:: generateFlyID(){
    char* flyID = (char*)malloc(4*sizeof(char));

    
    srand(this->seed);

    for(int i = 0; i < 3; i++)
        flyID[i] = (rand() % 26) + 'A';
    flyID[3] = '\0';

    return flyID;
}

int RandomGenerator:: genarateFuel(int C){
    srand(this->seed);

    return (rand() % C+1);
}

int RandomGenerator:: genarateEstimatedTime(int V){
    srand(this->seed);

    return (rand() % V+1);
}

int RandomGenerator:: generateEmergency(double Pe){
    srand(this->seed*(double)rand()/(double)RAND_MAX*100);

    if((double)rand()/(double)RAND_MAX <= Pe){
        return 1; // É um voo de emergência
    }
    return 0; // Não é um voo de emergência
}