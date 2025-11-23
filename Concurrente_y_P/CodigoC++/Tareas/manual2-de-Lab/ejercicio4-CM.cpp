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

//Recurso compartido - MONITOR
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


      void intentarFumar(int id){
          unique_lock<mutex> lk(candado);

          while (papelArroz < 1 || tabaco < 1 || cerillos < 1){
              recursoDisponible = false;
              vc.notify_all(); //Notificar al agente
              vc.wait(lk);
          }

          fumar();
          cout << "Fumador " << id << " fumando y escuchando tango... ";
          cout << "Quedan " << papelArroz << " papel arroz, " << tabaco << " tabaco y "
               << cerillos << " cerillos en la mesa." << endl;
        lk.unlock();
      }


      void reponerRecursos(){
          unique_lock<mutex> lk(candado);
          while (recursoDisponible){
              vc.wait(lk);
          }

          int repuesto = 1 + (rand() % 10);
          int papel = repuesto;
          int tab = repuesto;
          int cer = repuesto;

          agregarRecursos(papel, tab, cer);
          cout << "     AGENTE repuso - Papel: " << papelArroz
               << ", Tabaco: " << tabaco << ", Cerillos: " << cerillos << endl;

          recursoDisponible = true;
          vc.notify_all(); //Notificar a los fumadores
          lk.unlock();
      }
};

class Fumador{
    public:
      Mesa* mesa;
      int idFumador;

      Fumador(Mesa* mesa, int idFumador){
          this->mesa = mesa;
          this->idFumador = idFumador;
      }

      void operator()(){
          while (true){
              mesa->intentarFumar(idFumador);
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

      void operator()(){
          while (true){
              mesa->reponerRecursos();
              this_thread::sleep_for(chrono::milliseconds(900));
          }
      }
};

int main(){
    srand(time(NULL));
    Mesa* mesa = new Mesa(10,10,10);
    vector<thread> hilos;
    int numFumadores = 100;

    for (int i = 0; i < numFumadores; i++) {
        hilos.push_back(thread(Fumador(mesa,i + 1)));
    }
    hilos.push_back(thread(Agente(mesa)));

    for (int i = 0; i < hilos.size(); i++) {
        hilos[i].join();
    }

    return 0;
}