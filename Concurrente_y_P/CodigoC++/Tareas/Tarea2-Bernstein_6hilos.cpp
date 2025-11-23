#include <thread>
#include <iostream>
#include <vector>

using namespace std;

int A[9];

//dependiendo de inicio, llena las posiciones pares o impares
void llenarArreglo(int i, thread* hiloDependencia) {
    if(hiloDependencia != nullptr)
        hiloDependencia->join(); //espera a que el hilo par/impar termine

    A[i] = A[i-2] + 4;
    cout << "A[" << i << "] = " << A[i] << endl << flush;
}

int main(){
    //inicialización de los primeros 2 elementos útiles
    A[1] = 1;   
    A[2] = 2;

    vector<thread*> hilos(6);
    int i;

    hilos[0] = new thread(llenarArreglo, 3, nullptr); //el hilo con A[3] no tiene que esperar a nadie
    hilos[1] = new thread(llenarArreglo, 4, nullptr); //el hilo A[4] no tiene que esperar a nadie

    // c/ hilo siguiente depende del hilo 2 posiciones atrás
    for(i = 2; i < 6; i++) 
        hilos[i] = new thread(llenarArreglo, i+3, hilos[i-2]);
        
    hilos[4]->join();
    hilos[5]->join(); //main espera a que terminen los últimos hilos (par e impar)

    for (thread* hilo : hilos) delete hilo;

    return 0;
}