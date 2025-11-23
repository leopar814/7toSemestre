#include <cmath>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

mutex candado;
condition_variable vc;

//Recurso compartido
class Mesa{
    public:
      int papelArroz, tabaco, cerillos;
      bool recursoDisponible;

      Mesa(int papelArroz, int tabaco, int cerillos){
          this->papelArroz = papelArroz;
          this->tabaco = tabaco;
          this->cerillos = cerillos;
          recursoDisponible = true;
      }

      void fumar(){
          papelArroz--;
          tabaco--;
          cerillos--;
      }

      void agregarRecursos(int papel, int tab, int cer){
          papelArroz += papel;
          tabaco += tab;
          cerillos += cer;
      }
};


//Sincronizcion fuera del recurso compartido porque es version sin Monittores
class Fumador{
    public:
      Mesa* mesa;
      int id;

      Fumador(Mesa* mesa, int id){
          this->mesa = mesa;
          this->id = id;
      }

      void consumir(){
          mesa->fumar();
          cout << "Fumador " << id << " fumando y escuchando tango... ";
          cout << "Quedan " << mesa->papelArroz << " papel arroz, " << mesa->tabaco << " tabaco y "
               << mesa->cerillos << " cerillos en la mesa." << endl;
      }

      void operator()(){
          while (true){
              unique_lock<mutex> lk(candado);

              while (!(mesa->papelArroz >= 1 && mesa->tabaco >= 1 && mesa->cerillos >= 1)){
                  mesa->recursoDisponible = false;
                  vc.notify_all();
                  vc.wait(lk);
              }

              consumir();
              lk.unlock();

              this_thread::sleep_for(chrono::milliseconds(900));
          }
      }
};

class Agente{
    public:
      Mesa* mesa;

      Agente(Mesa* mesa){
          this->mesa = mesa;
      }

      bool puedeReponer(){
          return mesa->recursoDisponible;
      }

      void reponer(){
          int repuesto = 1 + (rand() % 10);
          int papel = repuesto;
          int tab = repuesto;
          int cer = repuesto;

          mesa->agregarRecursos(papel, tab, cer);
          cout << "     AGENTE repuso - Papel: " << mesa->papelArroz
               << ", Tabaco: " << mesa->tabaco << ", Cerillos: " << mesa->cerillos << endl;
      }

      void operator()(){
          while (true){
              unique_lock<mutex> lk(candado);

              while (puedeReponer()){
                  vc.wait(lk);
              }

              reponer();
              mesa->recursoDisponible = true;
              vc.notify_all();

              lk.unlock();

              this_thread::sleep_for(chrono::milliseconds(900));
          }
      }
};

int main(){
    srand(time(NULL));
    Mesa* mesa = new Mesa(5,5,5);
    vector<thread> hilos;
    int numFumadores = 150;

    for (int i = 0; i < numFumadores; i++) {
        hilos.push_back(thread(Fumador(mesa,i + 1)));
    }
    hilos.push_back(thread(Agente(mesa)));

    for (int i = 0; i < hilos.size(); i++) {
        hilos[i].join();
    }

    return 0;
}