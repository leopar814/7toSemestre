#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>
#include <chrono>

using namespace std;

mutex candado;
condition_variable vc;

class Tenedor {
public: 
    bool libre;

    Tenedor() {
        libre = true;
    }

    void tomarTenedor() {
        unique_lock<mutex> lk(candado);
        while(!libre) {
            vc.wait(lk);
        }
        libre = false;
    }

    void soltarTenedor() {
        unique_lock<mutex> lk(candado);
        libre = true;
        vc.notify_all();
    }
};

class Filosofo {
public: 
    int quiensoy;
    Tenedor *tenedorIzquierdo, *tenedorDerecho;

    Filosofo() {} // necesario para usar array<Filosofo,5>

    Filosofo(int quiensoy, Tenedor *tenedorIzquierdo, Tenedor *tenedorDerecho) {
        this->quiensoy = quiensoy;
        this->tenedorIzquierdo = tenedorIzquierdo;
        this->tenedorDerecho = tenedorDerecho;
    }

    void operator()() {
        for(int i = 0; i < 10; i++) {
            cout << "Filosofo " << quiensoy << " PENSANDO..." << endl;
            this_thread::sleep_for(chrono::milliseconds(500));

            if (quiensoy == 5) { // último filósofo cambia el orden
                tenedorDerecho->tomarTenedor();
                tenedorIzquierdo->tomarTenedor();
            } else {
                tenedorIzquierdo->tomarTenedor();
                tenedorDerecho->tomarTenedor();
            }

            cout << "Filosofo " << quiensoy << " COMIENDO..." << endl;
            this_thread::sleep_for(chrono::milliseconds(100));

            tenedorDerecho->soltarTenedor();
            tenedorIzquierdo->soltarTenedor();
        }
    }
};

int main() {
    array<Filosofo, 5> filosofos;
    array<Tenedor, 5> tenedores;
    array<thread, 5> hilos;

    // Asignar filósofos con sus tenedores
    for(int i = 0; i < 5; i++)
        filosofos[i] = Filosofo(i+1, &tenedores[i], &tenedores[(i+1)%5]);

    // Crear hilos
    for(int i = 0; i < 5; i++)
        hilos[i] = thread(ref(filosofos[i]));

    // Esperar que terminen
    for(int i = 0; i < 5; i++)
        hilos[i].join();

    return 0;
}
