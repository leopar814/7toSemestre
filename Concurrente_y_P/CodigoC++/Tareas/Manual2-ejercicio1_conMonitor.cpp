#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>

using namespace std;

mutex candado;
condition_variable vc;

class sumatoria{ //Monitor
    public:
        int limiteSumatoria;
        int suma, turno;
    public:
        sumatoria(int limiteSumatoria){
            this -> limiteSumatoria = limiteSumatoria;
            suma = 0;
            turno = 1;
        }

        void hacerSuma(int id){
            unique_lock<mutex> lk(candado);
                while(turno != id ){
                    vc.wait(lk);
                }
            lk.unlock();
            suma = suma + id;
            cout << "Hilo " << id << " suma parcial " << suma << endl;

        }

        void notificaSuma(){ 
            candado.lock();
                turno++;
                vc.notify_all();
            candado.unlock();
        }
};

class termino{
    public:
        int id;
        sumatoria *s;

    public:
        termino(int id, sumatoria *s){
            this -> id = id;
            this -> s = s;
        }

        void operator()(){
            s->hacerSuma(id);
            s->notificaSuma();
        }
};


int main(){
    const int limiteSumatoria = 10;

    sumatoria *s = new sumatoria(limiteSumatoria);

    array<thread *, limiteSumatoria> t;

    for(int i = 0; i < limiteSumatoria; i++){
        t[i] = new thread (termino(i + 1, s));
    }

    for(int i = 0; i < limiteSumatoria; i++){
        t[i]->join();
    }
    cout << "Sumatoria de i de " << limiteSumatoria << " términos es = " << s -> suma << endl;

    return 0;
}