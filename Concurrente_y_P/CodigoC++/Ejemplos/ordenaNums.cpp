#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>
#include <cstdlib>
#include <ctime>

using namespace std;

class Numero { // Recurso compartido
    public:
        int *num;

    public:
        Numero() {
            num = nullptr;
        }
        Numero(int *num) {
            this->num = num;
        }
};

class NodoOrdena {
    public:
        int id;
        Numero *number;
        int *miNumber;
    public:
        NodoOrdena() {
            number = nullptr;
            miNumber = nullptr;
        }
        NodoOrdena(int id, Numero *number) {
            this->id = id;
            this->number = number;
            miNumber = nullptr;
        }

        void operator()() {
            if(miNumber == nullptr)
                cout << "Hilo " << id << endl;
        }
};

int main() {

    const int limiteNumeros = 10;
    array<int, limiteNumeros> nums;
    array<thread *, limiteNumeros> hilos;
    Numero *n = new Numero();
    int i; // Iteraciones

    srand(static_cast<unsigned>(time(0))); // Inicialización de la semilla para aleatorios

    for(i = 0; i < limiteNumeros; i++)
        nums[i] = 1 + (rand() % 100);
    
    for(i = 0; i < limiteNumeros; i++)
        cout << nums[i] << endl;

    for(i = 0; i < limiteNumeros; i++)
        hilos[i] = new thread(NodoOrdena(i, n));

    for(i = 0; i < limiteNumeros; i++)
        hilos[i]->join();
    
    
    return 0;
}