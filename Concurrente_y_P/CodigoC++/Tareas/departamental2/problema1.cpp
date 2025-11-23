// Generación de números pares con sincronización de dos hilos alternados

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex candado;
condition_variable vc;

int num_generado = 0; // Recurso compartido
int turno = 1; // Alternancia de los hilos 

void generar_numero(int miTurno) {
    unique_lock<mutex> lk(candado);
    
    while(true) {

        while(turno != miTurno)
            vc.wait(lk);

        num_generado += 2; 
        cout << "Hilo " << miTurno << " generó el número: " << num_generado << endl;

        turno = (miTurno % 2) + 1; // {1, 2}
        vc.notify_one();
    } 
}


int main() {

    thread hilo1(generar_numero, 1);
    thread hilo2(generar_numero, 2);

    hilo1.join();
    hilo2.join();

    return 0;
}