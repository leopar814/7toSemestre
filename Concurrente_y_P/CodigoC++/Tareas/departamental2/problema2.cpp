#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;
const int MAX_PAPELES = 3;

mutex candado;
condition_variable vc;

class Mesa{
    public:
        int numPapeles;

        Mesa(){
            this->numPapeles = 0;
        }

        void colocarPapel(int id){
            unique_lock<mutex> lk(candado);
            while (numPapeles == MAX_PAPELES) {
                vc.wait(lk);
            }

            numPapeles++;
            cout<<"Persona "<<id<<" coloco un papel. Hay "<<numPapeles<<" papeles en la mesa"<<endl;

            //Notificar si la mesa esta llena
            if (numPapeles == MAX_PAPELES) {
                vc.notify_all();
            }
            lk.unlock();
        }

        void engraparPapel(){
            unique_lock<mutex> lk(candado);
            while (numPapeles<MAX_PAPELES) {
                vc.wait(lk);
            }

            cout<<"El engrapador agarro los "<<numPapeles<<" papeles y los engrapo. ";
            numPapeles = 0;
            cout<<"Papeles actuales: "<<numPapeles<<endl;
            //Notificar a las personas que pueden seguir engrapando
            vc.notify_all();

            lk.unlock();
        }
};

class Persona{
    public:
        int id;
        Mesa* mesa;

        Persona(int id, Mesa* mesa){
            this->id = id;
            this->mesa = mesa;
        }

        void operator()(){
            while (true) {
                mesa->colocarPapel(id);
                this_thread::sleep_for(chrono::milliseconds(300)); //Simular que la coloca  con el sleep
            }
        }
};

class Engrapador{
    public:
    Mesa* mesa;

    Engrapador(Mesa* mesa){
        this->mesa = mesa;
    }

    void operator()(){
        while (true) {
            mesa->engraparPapel();
            this_thread::sleep_for(chrono::milliseconds(500)); //Simular que engrapa el papel con el sleep
        }
    }
};

int main(){
    Mesa* mesa = new Mesa();
    vector<thread> hilos;

    for (int i = 0; i < 3; i++) {
        hilos.push_back(thread(Persona(i+1,mesa)));
    }
    hilos.push_back(thread(Engrapador(mesa)));

    for (int i = 0; i < hilos.size(); i++) {
        hilos[i].join();
    }

    return 0;
}
