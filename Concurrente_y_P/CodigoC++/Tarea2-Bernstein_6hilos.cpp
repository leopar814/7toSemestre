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

    hilos[0] = new thread(llenarArreglo, 3, nullptr); //el primer hilo de A[impar] no tiene que esperar a nadie
    hilos[1] = new thread(llenarArreglo, 4, nullptr); //el primer hilo A[par] no tiene que esperar a nadie

    for(i = 5; i < 9; i++) 
        hilos[i-3] = new thread(llenarArreglo, i, hilos[i-5]);
        
    hilos[4]->join();
    hilos[5]->join(); //main espera a que terminen los últimos hilos (par e impar)

    for (thread* hilo : hilos) delete hilo;

    return 0;
}