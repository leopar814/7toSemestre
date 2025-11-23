/*
Implemente en C++ un programa concurrente que genere una barrera. Una
barrera es un punto de sincronización entre varios threads. Se caracteriza porque los
threads que van llegando a ella esperan hasta que llega el último. Por ejemplo, se
pueden sincronizar N threads y hasta que el último no llegue los demás no deben poder
continuar. Implemente un programa concurrente en C++ utilizando wait-notify con y sin
monitores, que resuelva dicha aseveración. Lancé unos pocos threads (con cuatro es
razonable), cada uno que espere un tiempo proporcional a su identificador (en
segundos), y luego imprima un mensaje que lo identifique y una vez que haya llegado a
la barrera espere en ella a que el resto de Threads lleguen para poder terminar.
Introduzca un ciclo en el run de los threads para ver cómo se van acercando a la barrera
hasta llegar a ella. La programación la podrán hacer con monitores o sin monitores.

----------Versión con monitores--------------------
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>
#include <chrono>

using namespace std;

mutex candado;
condition_variable vc;

class Barrera{ //Monitor
    public:
        int totalHilos;
        int hilosEnBarrera;

    public:
        Barrera(int total){
            totalHilos = total;
            hilosEnBarrera = 0;
        }

        void esperar(int id){
            unique_lock<mutex> lk(candado);
                hilosEnBarrera++;//el hilo ha llegado a la barrera   
                cout << "HILO " << id << " ESPERANDO EN LA BARRERA (" << hilosEnBarrera << "/" << totalHilos << ")" << endl;
                               
                //si aún no han llegado todos, espera
                if(hilosEnBarrera < totalHilos){
                    vc.wait(lk);
                }else{
                    cout << "TODOS LOS HILOS LLEGARON AL FINAL" << endl;
                    vc.notify_all();//el ultimo hilo despierta a todos
                }
        }
};

class Hilo{
    public:
        int id;
        Barrera* barrera;

    public:
        Hilo(int id, Barrera* barrera ){
            this -> id = id;
            this -> barrera= barrera;
        }

        void operator()(){
            for(int cont = 0; cont < 10; cont++){
                cout << "hilo " << id << " acercandose a la barrera: " << cont << endl;
                this_thread::sleep_for(chrono::milliseconds(100 * id));
            }

            barrera -> esperar(id);
        }
};


int main(){
    const int num_hilos = 4;
    Barrera* barrera = new Barrera(num_hilos); //Capacidad de la caja
    array<thread*, num_hilos> hilos;

    for (int i = 0; i <num_hilos; i++) {
        hilos[i] = new thread(Hilo(i + 1, barrera));
    }

    for (int i = 0; i < num_hilos; i++) { 
        hilos[i]->join();
    }

    return 1;
}