#include <iostream>
#include <thread>

using namespace std;

int j = 0, k = 0, a[2]; 

void S1() { j += 10; }
void S2() { k += 100; }
void S3() { a[0] = j * k; }
void S4() { j += 10; }
void S5() { k += 100; }
void S6() { a[1] = j * k; }
void S7() { cout << "j = " << j << ", k = " << k << endl; }
void S8() { cout << "a[0] = " << a[0] << endl; }
void S9() { cout << "a[1] = " << a[1] << endl; }

int main() {

    // S1 y S2 en paralelo
    thread hilo1(S1);
    thread hilo2(S2);
    hilo1.join();
    hilo2.join();

    // S3 depende de S1 y S2
    thread hilo3(S3);
    hilo3.join();

    // S4, S5 y S8 dependen de S3
    thread hilo4(S4);
    thread hilo5(S5);
    thread hilo8(S8);
    hilo4.join();
    hilo5.join();

    // S6 y S7 dependen de S4 y S5
    thread hilo6(S6);
    thread hilo7(S7);
    hilo6.join();

    // S9 depende de S6
    thread hilo9(S9);

    // Últimas instrucciones del programa
    hilo7.join();
    hilo8.join();
    hilo9.join();


    return 0;
} 