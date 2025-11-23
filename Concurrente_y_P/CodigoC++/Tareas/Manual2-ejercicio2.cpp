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
            vc.wait(lk);
        }
        hojas++;
        cout << "Trabajador " << id << " puso la hoja " << hojas << endl;
        vc.notify_all(); // Notifica al observador
    }

    void vaciarCaja() {
        unique_lock<mutex> lk(candado);
        while (hojas < capacidad) {
            vc.wait(lk);
        }
        cout << "La caja llegó a 100 hojas. Observador la vacía.\n";
        hojas = 0;
        vc.notify_all(); // Notifica a los trabajadores
    }
};

class Trabajador {
public:
    int id;
    Caja* caja;

    Trabajador(int id, Caja* caja) {
        this->id = id;
        this->caja = caja;
    }

    void operator()() {
        for (int i = 0; i < 100; i++) {
            caja->colocarHoja(id);
            //this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
};

class Observador {
public:
    Caja* caja;

    Observador(Caja* caja) {
        this->caja = caja;
    }

    void operator()() {
        for (int i = 0; i < 3; i++) { // Vacía la caja 3 veces
            caja->vaciarCaja();
            //this_thread::sleep_for(chrono::milliseconds(50));
        }
    }
};

int main() {
    Caja* caja = new Caja(100);
    array<thread*, 4> hilos;

    for (int i = 0; i < 3; i++) {
        hilos[i] = new thread(Trabajador(i + 1, caja));
    }

    hilos[3] = new thread(Observador(caja));

    for (int i = 0; i < 4; i++) {
        hilos[i]->join();
    }

    return 1;
}