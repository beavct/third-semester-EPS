#pragma once

class File{
    protected:
        int T;
        int K;
        double Pp;
        double Pd;
        double Pe;
        int C;
        int V;
    public:
        File();
        ~File();
        void readFile();
        int getT();
        int getK();
        double getPp();
        double getPd();
        double getPe();
        int getC();
        int getV();
};