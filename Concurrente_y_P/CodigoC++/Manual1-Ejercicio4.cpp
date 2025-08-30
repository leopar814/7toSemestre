// Fórmula General Cuadrática Multihilo
#include <iostream>
#include <thread>
#include <cmath>

using namespace std;

int f, g, h, k, l, m, x1, x2;
int a, b, c;

void funcS1() {
    f = 4 * a * c;
    cout << "f : " << f << endl << flush;
}

void funcS2() {
    g = b * b;
    cout << "g : " << g << endl << flush;
}

void funcS3(thread* hiloDependencia1, thread* hiloDependencia2) {
    if(hiloDependencia1 != nullptr) 
        hiloDependencia1->join();
    if(hiloDependencia2 != nullptr) 
        hiloDependencia2->join();

    h = sqrt(g - f);
    cout << "h : " << h << endl << flush;
}

void funcS4(thread* hiloDependencia) {
    if(hiloDependencia != nullptr)
        hiloDependencia->join();

    k = -b + h;
    cout << "k : " << k << endl << flush;
}

void funcS5(thread* hiloDependencia) {
    if(hiloDependencia != nullptr)
        hiloDependencia->join();

    l = -b - h;
    cout << "l : " << l << endl << flush;
}

void funcS6() {
    m = 2 * a;
    cout << "m : " << m << endl << flush;
}

void funcS7(thread* hiloDependencia1, thread* hiloDependencia2) {
    if(hiloDependencia1 != nullptr) 
        hiloDependencia1->join();
    if(hiloDependencia2 != nullptr) 
        hiloDependencia2->join();

    x1 = k / m;
    cout << "x1 : " << x1 << endl << flush;
}

void funcS8(thread* hiloDependencia1, thread* hiloDependencia2) {
    if(hiloDependencia1 != nullptr) 
        hiloDependencia1->join();
    if(hiloDependencia2 != nullptr) 
        hiloDependencia2->join();
    
    x2 = l / m;
    cout << "x2 : " << x2 << endl << flush;
}

int main() {
    cout << "Ingrese a: ";
    cin >> a;
    cout << "Ingrese b: ";
    cin >> b;
    cout << "Ingrese c: ";
    cin >> c;

    thread hilo1(funcS1);
    thread hilo2(funcS2);
    thread hilo6(funcS6);
    thread hilo3(funcS3, &hilo1, &hilo2);
    thread hilo4(funcS4, &hilo3);
    thread hilo5(funcS5, &hilo3);
    thread hilo7(funcS7, &hilo4, &hilo6);
    thread hilo8(funcS8, &hilo5, &hilo6);

    hilo7.join();
    hilo8.join();
    
    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;

    return 0;
}