#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>

using namespace std;

class Monitor
   {
    public:
       int i;
       mutex candado;
       condition_variable cv2;
       array<condition_variable, 10> cv;
       
    public:
       Monitor() { i = 0; }
       
       void bloquear(int id) 
          {
           unique_lock<mutex> lk(candado);
              cout << "ProcesoBloqueado " << id << "se bloquea...y se almacena en la casilla " << i << "\n";
              i++;
              cv2.notify_one();
              cv[i-1].wait(lk);
                  
              //this_thread::sleep_for(chrono::milliseconds(500));
              cout << "ProcesoBloqueado " << id << "se ha liberado...\n";
           lk.unlock();
          }
       
       void liberar() {
           unique_lock<mutex> lk(candado);
              while(i <= 9)
                 cv2.wait(lk);
            
              for(int i = 0; i <= 9; i++) {
                  cv[i].notify_one();
                  std::this_thread::sleep_for(std::chrono::milliseconds(1));
               }
              cout << "LIBERARDOR liberando los procesos...\n";
           lk.unlock();
          }
   };



class ProcesoBloqueado {
    public:
        int id;
        Monitor *m;
    
    public:
        ProcesoBloqueado():id(0){}
        
        ProcesoBloqueado(int id, Monitor *m)
           {
            this->id=id;
            this->m=m;
           }
        
        void operator()()
           { 
            m->bloquear(id);
           }
   };

class ProcesoLiberador  {
     public:
         string cad;
         Monitor *m;
     public: 
        ProcesoLiberador(string cad, Monitor *m)
           {
            this->cad=cad;
            this->m=m;
           }
        
        void operator()()
           {
            m->liberar();
           }
        
    };

int main() {
   array<ProcesoBloqueado, 10> p; 
   array<thread, 10> h;
   Monitor *m = new Monitor();
   
   ProcesoLiberador liberador("LIBERADOR", m);
   thread l(liberador);
   
   for(int i = 0; i < 10; i++)
      p[i] = ProcesoBloqueado(i + 1, m);

   for(int i = 0; i < 10; i++)
      h[i] = thread(p[i]);
   
   for(int i = 0; i < 10; i++)
      h[i].join();
    
    l.join();
    return 1;
   }

