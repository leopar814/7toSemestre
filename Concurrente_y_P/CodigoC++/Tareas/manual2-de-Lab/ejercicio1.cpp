#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>

using namespace std;

mutex candado;
condition_variable vc;

int suma = 0, turno = 1;

void hacerSuma(int id) {
    unique_lock<mutex> lk(candado);
    while(turno < id)// Término i espera a los anteriores
        vc.wait(lk);
    suma += id;
    cout << "Hilo " << id << " -> Suma parcial = " << suma << endl;
}

void notificaSuma() { 
    lock_guard<mutex> lk(candado);
    turno++;
    vc.notify_all();
}

void termino(int id) {
    hacerSuma(id);
    notificaSuma();
};


int main() {
    const int limiteSumatoria = 100;
    array<thread, limiteSumatoria> hilos;
    int i; // iterador

        for(i = 0; i < limiteSumatoria; i++)
            hilos[i] = thread(termino, i + 1);

        for(i = 0; i < limiteSumatoria; i++)
            hilos[i].join();

        cout << "Sumatoria de " << limiteSumatoria << " términos = " << suma << endl;

    return 0;
}