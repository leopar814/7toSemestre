/*

*/
#include <thread>
#include <iostream>
#include <vector>

using namespace std;

void imprimirLetra(char letra, thread* hilo) {
    if(hilo != nullptr)
        hilo->join();
    cout << letra << flush ;
} 
    
int main() {
    string word;

    cout << "Ingrese una palabra: ";
    cin >> word;

    vector<thread*> hilos(word.size());
    int opc, i;

    do {
        cout << "Cómo quieres la ejecución? \n1. Secuencial\n2. Paralela" << endl;
        cout << "Digita la opción: ";
        cin >> opc;

        switch (opc) {
            case 1: {
                hilos[0] = new thread(imprimirLetra, word[0], nullptr);
                
                for(i = 1; i < word.size(); i++)
                    hilos[i] = new thread(imprimirLetra, word[i], hilos[i-1]);
                
                //main espera a que termine el último hilo
                hilos.back()->join();
                break;
            }
            case 2: {
                for(i = 0; i < word.size(); i++) 
                    hilos[i] = new thread(imprimirLetra, word[i], nullptr);
                
                //main espera a que terminen todos los hilos (paralelo)
                for(thread* hilo: hilos)
                    hilo->join();
                break;
            }
            default: {
                cout << "Esa opción no es válida\n" << endl;
                break;
            }
        }
    } while((opc != 1) && (opc != 2)); 

    cout << endl; //para que no se vea amontonado jeje

    //Se limpia la memoria de los threads
    for (thread* hilo : hilos) delete hilo;

    return 0;
}