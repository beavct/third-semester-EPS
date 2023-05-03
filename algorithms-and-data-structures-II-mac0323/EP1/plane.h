#pragma once

class Plane {
    protected:
        char* companyID;
        char* flyID;
        int emergency;
        int action;
        int extraInfo; // Fuel or estimated time 
        int priority;
        int timeWaiting;
        double perTime;

    public:
        Plane(double Pp, double Pd, double Pe, int C, int V, int i);
        ~Plane();
        char* getCompanyID();
        char* getFlyID();
        int getEmergency();
        int getExtraInfo();
        int getAction();
        int getTimeWaiting();
        int getPriority();
        double getPerTime();
        void setExtraInfo(int x);
        void setTimeWaiting(int x);
        void setPrior(int i);
};