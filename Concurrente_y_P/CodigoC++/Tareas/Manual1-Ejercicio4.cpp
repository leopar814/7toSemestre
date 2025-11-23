// Fórmula General Cuadrática Multihilo
#include <iostream>
#include <thread>
#include <cmath>

using namespace std;

int f, g, h, k, l, m, x1, x2;
int a, b, c;

void funcS1() {
    f = 4 * a * c;
    cout << "f : " << f << endl;
}

void funcS2() {
    g = b * b;
    cout << "g : " << g << endl;
}

void funcS3(thread* hilo1, thread* hilo2) {
    hilo1->join();
    hilo2->join();

    h = sqrt(g - f);
    cout << "h : " << h << endl;
}

void funcS4(thread* hilo3) {
    if(hilo3->joinable())
        hilo3->join();
    cout << "Calculando k..." << endl;
    k = -b + h;
    cout << "k : " << k << endl;
}

void funcS5(thread* hilo3) {
    if(hilo3->joinable())
        hilo3->join();
    cout << "Calculando l..." << endl;
    l = -b - h;
    cout << "l : " << l << endl;
}

void funcS6() {
    m = 2 * a;
    cout << "m : " << m << endl;
}

void funcS7(thread* hilo4, thread* hilo6) {
    hilo4->join();
    if(hilo6->joinable()) 
        hilo6->join();

    x1 = k / m;
    cout << "x1 : " << x1 << endl;
}

void funcS8(thread* hilo5, thread* hilo6) {
    hilo5->join();
    if(hilo6->joinable()) 
        hilo6->join();
    
    x2 = l / m;
    cout << "x2 : " << x2 << endl;
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

    return 0;
}