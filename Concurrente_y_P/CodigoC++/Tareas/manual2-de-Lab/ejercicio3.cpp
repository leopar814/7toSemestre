/*
3. N matemáticos llevan a cabo la suma de los primeros k números naturales (con N<=k)
en paralelo. Cada matemático ira tomando (de un arreglo de enteros) números que
sumará de forma parcial. Cuando todos los números han sido procesados por los
matemáticos, cada uno de ellos tendrá ya su suma parcial contabilizada y sumarán a
una variable global compartida dichos resultados parciales para obtener el resultado
final de la suma. Implemente la solución concurrente de este problema en C++ usando
wait-notify sin monitores.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

int N = 10; //cantidad de matemáticos
int k = 100; //cantidad de numeros naturales
int posicion = 0;//indice compartido, numero a tomar
int sumaGlobal = 0;//suma acumulada final
vector<int> numeros;//vector que contiene los números naturales

mutex candado;
condition_variable vc;

class Matematico{
    public:
        int id;
        int sumaParcial;

    public:
        Matematico(int id){
            this -> id = id;
            this -> sumaParcial = 0;
        }

        void operator()(){
            while(true){
                unique_lock<mutex> lk(candado);

                    if(posicion >= k){ //si no hay más numeros por procesar
                        vc.notify_all();//Notifica a todos los hilos para que despierten y agregen su suma a la total
                        break;
                    }

                    int num = numeros[posicion];//toma el numero del vector
                    posicion++;//se incrementa la posición
                    sumaParcial += num;//añade el num a la suma parcial del matematico
                    cout << "Matematico " << id << " toma " << num << endl;

                vc.notify_all();//Notifica a todos los hilos que se cambió la posición
                vc.wait(lk);//espera a que otro hilo tome un numero
            }

            unique_lock<mutex> lk(candado);
                sumaGlobal += sumaParcial;//agrega su suma parcial al la suma global compartida
                cout << "SUMA PARCIAL FINAL DEL MATEMATICO " << id << " = " << sumaParcial << endl;
        }
};

int main(){
    // Inicializar el arreglo con números naturales
    for(int i = 1; i <= k; i++){
        numeros.push_back(i);
    }

    vector<thread> hilos;

    for(int i = 0; i < N; i++){
        hilos.push_back(thread(Matematico(i+1)));
    }

    for(int i = 0; i < N; i++){
        hilos[i].join();
    }

    cout << "RESULTADO FINAL DE LA SUMA = " << sumaGlobal << endl;

    return 0;
}