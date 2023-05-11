#include <string>

using namespace std;

class Item{
    protected:
        int nOcorrencias;
        int tam;
        int vogaisDif;
    public:
        Item(){

        }
        ~Item(){

        }
        void setNOcorrencias(int x){
            this->nOcorrencias = x;
        }
        void setTam(int x){
            this->tam = x;
        }
        void setVogaisDif(int x){
            this->vogaisDif = x;
        }
        int getNOcorrencias(){
            return this->nOcorrencias;
        }
        int getTam(){
            return this->tam;
        }
        int getVogaisDif(){
            return this->vogaisDif;
        }
};
