#include <thread>
#include <iostream>

using namespace std;

int A[9];

void llenarArreglo(int inicio) {
    for(int i = inicio; i < 9; i+=2) {
        A[i] = A[i-2] + 4;
        cout << "A[" << i << "] = " << A[i] << endl << flush;
    }
}

int main(){
    //inicialización de los primeros 2 elementos útiles
    A[1] = 1;   
    A[2] = 2;

    thread* hilo1 = new thread(llenarArreglo, 3);
    thread* hilo2 = new thread(llenarArreglo, 4);
    
    hilo1->join();
    hilo2->join();

    delete hilo1;
    delete hilo2;

    return 1;
}