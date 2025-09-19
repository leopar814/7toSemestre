#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// Variables globales
vector<int> cajas;
int totalHojas = 0;

void persona(int id, int numHojas) {
    for (int i = 0; i < numHojas; i++){
        cajas[id]++;
        cout << "Persona " << id + 1 << " colocando hoja, " << cajas[id] << " hojas en total" << endl;
    }
}

void engrapador(vector<thread> &hilosPersonas, int numPersonas) {
    // El engrapador espera a que todas las personas terminen
    for (int i = 0; i < numPersonas; ++i){
        hilosPersonas[i].join();
    }
    totalHojas = 0;
    for (int i = 0; i < numPersonas; i++){
        totalHojas = totalHojas + cajas[i];
    }
    cout << "Total de hojas engrapadas: " << totalHojas << endl;
}

int main() {
    // Inicializar semilla para numeros aleatorios
    srand(time(0));
    // Personas aleatorias(entre 2 y 10)
    int numPersonas = rand() % 9 + 2;
    cajas.resize(numPersonas, 0);

    // Vector de el numero de hojas para cada persona
    vector<int> hojasPersona(numPersonas);
    vector<thread> hilosPersonas;

    // Hojas aleatorias(entre 50 y 100)
    for (int i = 0; i < numPersonas; i++) {
        hojasPersona[i] = rand() % 51 + 50;
        cout << "Persona " << i+1 << ": " << hojasPersona[i] << " hojas" << endl;
    }
    for (int i = 0; i < numPersonas; i++) {
        hilosPersonas.emplace_back(persona, i, hojasPersona[i]);
    }

    // Hilo engrapador, se usa ref() para evitar copia del vector
    thread hiloEngrapador(engrapador, ref(hilosPersonas), numPersonas);
    hiloEngrapador.join();

    return 0;
}