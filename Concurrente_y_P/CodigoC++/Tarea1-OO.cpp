#include <thread>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class palabra {
    public:
        char letra;

    public:
        palabra(char letra) {
            this->letra = letra;
        }

        void operator()() {
            cout << letra << flush;
        }

};

int main() {
    string cadena;
    cout << "Ingrese una palabra: ";
    cin >> cadena;
    cout << endl;
    
    vector<thread*> hilos [cadena.size()];
    vector<palabra*> obj [cadena.size()];

    for(int i = 0; i < cadena.size(); i++) {
        obj[i] =new palabra(cadena[i]);
    }

    for(int i = 0; i < cadena.size(); i++) {
        hilos[i] =  new thread(obj[i]);
    }

    for(auto hilo : hilos) 
        hilo->join();

    for (auto hilo : hilos) delete hilo;

    for (auto objPtr : obj) delete objPtr;
    
    cout << endl; //para que no se vea amontonado jeje

    return 0;
}