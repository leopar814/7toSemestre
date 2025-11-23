
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

mutex candado;
condition_variable vc;

class Tenedor { //MONITOR
   public:
     bool libre;

   public:
     Tenedor() {
       	libre=true;
      }

      void tomarTenedor(int quienSoy, int numTenedor) {
         while(!libre) {
            unique_lock<mutex> lk(candado);
               vc.wait(lk);
            lk.unlock();
            }
         candado.lock();
         if (numTenedor == 1)
            cout << "Filosofo " << quienSoy << " logro tomar tenedor Derecho" << endl;
         else 
            cout << "Filosofo " << quienSoy << " logro tomar tenedor Izquierdo" << endl;
         candado.unlock();
         libre = false;  
      }

      void soltarTenedor(int quienSoy, int numTenedor) {
         candado.lock();
         if (numTenedor == 1)
            cout << "Filosofo " << quienSoy << " logro SOLTAR tenedor Derecho" << endl;
         else 
            cout << "Filosofo " << quienSoy << " logro SOLTAR tenedor Izquierdo" << endl;
         candado.unlock();
         libre = true;
         unique_lock<mutex> lk(candado);
            vc.notify_all();
         lk.unlock();
      }
};


class Contador {
   public:
      int cont;
      int tope;

   public:
      Contador(int tope) {
         cont = 0;
         this->tope = tope;
      }

      void inc() {
         while(cont == tope) {
            unique_lock<mutex> lk(candado);
            vc.wait(lk);
            lk.unlock();
         }     
          cont++;
          cout << cont << "filosofos en la mesa...\n";   
         }

      void dec() {
         cont--;
         cout << cont << "filosofos en la mesa...\n";
         candado.lock();
            vc.notify_all();
         candado.unlock();
      }

      int getValor() {
         return cont;
      }
};


class Filosofo {
    public:
      int quienSoy;
      Contador *cnt;
      Tenedor *tenedorIzq, *tenedorDer;
      int numeroDeComidas;

    public:
       Filosofo(int quienSoy, Contador *cnt, Tenedor *tenedorIzq, Tenedor *tenedorDer)
          {
           this->quienSoy=quienSoy;
           this->cnt=cnt;
           this->tenedorIzq=tenedorIzq;
           this->tenedorDer=tenedorDer;
           numeroDeComidas=10;
          }

       void operator()() {
         for(int i = 1; i <= numeroDeComidas; i++) {
            candado.lock();
            cout << "Filosofo " << quienSoy << "PENSANDO..." << endl;
            candado.unlock();
            
            this_thread::sleep_for(chrono::milliseconds(100));
            cnt->inc(); //quiero sentarme en la mesa...
            tenedorDer->tomarTenedor(quienSoy,1);
            tenedorIzq->tomarTenedor(quienSoy,2);
            candado.lock();
            cout << "Filosofo " << quienSoy << "COMIENDO..." << endl;
            candado.unlock();
            this_thread::sleep_for(chrono::milliseconds(100));
            tenedorDer->soltarTenedor(quienSoy,1);
            tenedorIzq->soltarTenedor(quienSoy,2);
            cnt->dec(); //me paro de la mesa...
         }
         
         cout << "Filosofo " << quienSoy << "TERMINE..." << endl;
         }
   };

int main() {
    vector<thread> hilos;
    vector<Tenedor *> tenedores;
    int numFilosofos = 5;

    Contador *cnt = new Contador(numFilosofos - 1);

    for(int i = 0; i < numFilosofos; i++) {
         tenedores.push_back(new Tenedor());		
    	}
    
    for (int i = 0; i < numFilosofos; i++) {
        hilos.push_back(thread(Filosofo(i + 1, cnt, tenedores[i], tenedores[(i + 1) % numFilosofos])));
       }

    for(int i = 0; i < numFilosofos;  i++)
        hilos[i].join();

    return 1;
   }

