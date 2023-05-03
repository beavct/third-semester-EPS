#pragma once

class RandomGenerator{
    protected:
        int seed;
    public:
        RandomGenerator(int i);
        ~RandomGenerator();
        void generateFlyInfo(double Pp, double Pd, double Pe, int C, int V);
        int genarateAction(double Pp, double Pd);
        char* genarateCompanyID();
        char* generateFlyID();
        int genarateFuel(int C);
        int genarateEstimatedTime(int V);
        int generateEmergency(double Pe);
};