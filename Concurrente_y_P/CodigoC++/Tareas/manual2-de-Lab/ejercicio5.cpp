// Problema de los amigos comelones
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

mutex candado_out;


class Cacerola { // Monitor
    private: 
        mutex candado;
        condition_variable vc;  

        int raciones;
        int MAX_RACIONES;
    public:
        Cacerola(int raciones) {
            this->raciones = raciones;
            MAX_RACIONES = raciones;
        }

        void comerRacion(int id) {
            unique_lock<mutex> lk(candado);
            cout << "Amigo " << id << " intenta comer -> ";
            // Primero tiene que avisar al cocinero para que despierte
            while(raciones == 0) {
                cout << "Despierta al cocinero" << endl;
                raciones--; // Cocinero espera -1 para despertar
                vc.notify_all();
                vc.wait(lk);
            }
            raciones--;
            cout << "Amigo " << id << " comiendo una ración | Raciones restantes = " << raciones << endl;
            vc.notify_all();
        }

        void rellenar() {
            unique_lock<mutex> lk(candado);
            while(raciones >= 0)
                vc.wait(lk);
            cout << "Cocinero despertó..." << endl;
            raciones = MAX_RACIONES;
            cout << "Cocinero ha rellenado la cacerola con " << MAX_RACIONES << " raciones" << endl;
            vc.notify_all();
        }

        
};

class Amigo {
    private:
        int id;
        Cacerola *cacerola;

    public:
        Amigo(int id, Cacerola *cacerola) {
            this->id = id;
            this->cacerola = cacerola;
        }

        void hacerLimpieza(int tiempo) {
            this_thread::sleep_for(chrono::seconds(tiempo));
            lock_guard<mutex> lk(candado_out);
            cout << "Amigo " << id << " haciendo limpieza..." << endl;
        }

        void operator()() {
            do {
                cacerola->comerRacion(id);
                hacerLimpieza(1 + rand() % 3);
            } while (true);
        }
};

class Cocinero {
    private:
        Cacerola *cacerola;

    public:
        Cocinero(Cacerola *cacerola) {
            this->cacerola = cacerola;

        }

        void operator()() {
            do {
                cout << "Cocinero durmiendo..." << endl;
                cacerola->rellenar();
            } while (true);            
        }
};

int main() {
    srand(time(NULL));
    const int CANT_AMIGOS = 5;
    const int MAX_RACIONES = 10;

    Cacerola *cacerola = new Cacerola(MAX_RACIONES);
    Cocinero cocinero(cacerola);
    vector<thread> hilosAmigos;
    int i; // iterador

    for(i = 0; i < CANT_AMIGOS; i++)
        hilosAmigos.emplace_back(Amigo(i + 1, cacerola));
    
    thread hiloCocinero(cocinero);

    for(thread &hilo: hilosAmigos)
        hilo.join();

    hiloCocinero.join();
    return 0;
}