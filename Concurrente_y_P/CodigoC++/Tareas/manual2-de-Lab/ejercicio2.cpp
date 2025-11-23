#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>

using namespace std;

mutex candado;
condition_variable vc;

class Caja { // Monitor
public:
    int hojas;
    int capacidad;

    Caja(int capacidad) {
        this->capacidad = capacidad;
        hojas = 0;
    }

    void colocarHoja(int id) {
        unique_lock<mutex> lk(candado);
        while (hojas == capacidad) {
            vc.wait(lk); //espera si la caja está llena a que el observador la vacíe
        }
        hojas++;
        cout << "Trabajador " << id << " puso la hoja " << hojas << endl;
        if (hojas == capacidad) {
            vc.notify_all(); // Notifica al observador
        }
    }

    void vaciarCaja() {
        unique_lock<mutex> lk(candado);
        while (hojas < capacidad) {
            vc.wait(lk); // Espera hasta que la caja esté llena para poder vaciarla.
        }
        cout << "La caja llegó a 100 hojas. Observador la vacía.\n";
        hojas = 0;
        vc.notify_all(); // Notifica a los trabajadores
    }
};

class Trabajador { //Se colocan hojas hasta que see llena la caja
public:
    int id;
    Caja* caja;

    Trabajador(int id, Caja* caja) {
        this->id = id;
        this->caja = caja;
    }

    void operator()() {
        while(true){
            caja->colocarHoja(id);
            this_thread::sleep_for(chrono::milliseconds(300)); //Sleep necesario para ver orden en la ejeecucion
        }
    }
};

class Observador { //Se espera a que la caja se vacie continuamente
public: 
    Caja* caja;

    Observador(Caja* caja) {
        this->caja = caja;
    }

    void operator()() {
            while(true){
            caja->vaciarCaja();
            this_thread::sleep_for(chrono::milliseconds(300)); 
            }
    }
};

int main() {
    Caja* caja = new Caja(100); //Capacidad de la caja
    array<thread*, 4> hilos; //arreglo de 4 punteros (3 trabajadores y 1 observador)

    for (int i = 0; i < 3; i++) {
        hilos[i] = new thread(Trabajador(i + 1, caja)); 
    }

    hilos[3] = new thread(Observador(caja));

    for (int i = 0; i < 4; i++) { 
        hilos[i]->join();
    }

    return 1;
}
