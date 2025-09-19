#include <iostream>
#include <thread>

using namespace std;

int j = 0, k = 0, a[2]; 

void S1() {
    j = j + 10;
}

void S2() {
    k = k + 100;
}

void S3(thread* hiloDependencia1, thread* hiloDependencia2) {
    if (hiloDependencia1->joinable())
        hiloDependencia1->join();
    if (hiloDependencia2->joinable())
        hiloDependencia2->join();

    a[0] = j * k;
}

void S4(thread* hiloDependencia) {
    if (hiloDependencia->joinable())
        hiloDependencia->join();
    j = j + 10;
}

void S5(thread* hiloDependencia) {
    if (hiloDependencia->joinable())
        hiloDependencia->join();
    k = k + 100;
}

void S6(thread* hiloDependencia1, thread* hiloDependencia2) {
    if (hiloDependencia1->joinable())
        hiloDependencia1->join();
    if (hiloDependencia2->joinable())
        hiloDependencia2->join();

    a[1] = j * k;
}

void S7(thread* hiloDependencia1, thread* hiloDependencia2) {
    if (hiloDependencia1->joinable())
        hiloDependencia1->join();
    if (hiloDependencia2->joinable())
        hiloDependencia2->join();

    cout << "j = " << j << ", k = " << k << endl;
}

void S8(thread* hiloDependencia) {
    if (hiloDependencia->joinable())
        hiloDependencia->join();

    cout << "a[0] = " << a[0] << endl;
}

void S9(thread* hiloDependencia) {
    if (hiloDependencia->joinable())
        hiloDependencia->join();

    cout << "a[1] = " << a[1] << endl;
}

int main() {

    thread hilo1(S1);
    thread hilo2(S2);
    thread hilo3(S3, &hilo1, &hilo2);
    thread hilo4(S4, &hilo3);
    thread hilo5(S5, &hilo3);
    thread hilo6(S6, &hilo4, &hilo5);
    thread hilo7(S7, &hilo4, &hilo5);
    thread hilo8(S8, &hilo3);
    thread hilo9(S9, &hilo6);

    hilo7.join();
    hilo8.join();
    hilo9.join();


    return 0;
} 