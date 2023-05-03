#pragma once

class Runway{
    protected:
        int coolDown;
    public:
        Runway();
        ~Runway();
        int getCoolDown();
        void addCoolDown();
        void subCoolDown();
};