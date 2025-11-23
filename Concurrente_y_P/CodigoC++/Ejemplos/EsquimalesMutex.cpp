
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex candado;

class Agujero
   {
   	public:
    	int numPeces;

    public:
    	Agujero(int numPeces)
    	   {
    	   	this->numPeces=numPeces;
    	   }
        
        void pescar()
           {
           	numPeces--;
           }

    	int getPeces()
    	   {
    	   	return numPeces;
    	   }
   };

class Esquimales
   {
    public:
      string id;
      Agujero *hoyo;
      int contadorPeces;

    public:
      Esquimales(string id, Agujero *hoyo)
          {
           contadorPeces=0;
           this->id=id;
           this->hoyo=hoyo;
          }

      void operator()()
         {
          while(true)
          	{
          	 candado.lock();
          	 if (hoyo->getPeces()>0)
          	     {
                  hoyo->pescar();
                  contadorPeces++;
                  cout << id << " Ha pescado: " << contadorPeces << "peces" << "QUEDAN " << hoyo->getPeces() << "peces\n";
          	     }
          	  else {
          	        candado.unlock();
                    break;
          	       } 
          	 candado.unlock();
          	}
          cout << id << "Total de peces pescados= " << contadorPeces << "\n";
         }
   
   };

int main()
   {
    Agujero *hoyo=new Agujero(100);
    Esquimales esq1("Esquimal 1",hoyo);
    Esquimales esq2("Esquimal 2",hoyo);

    thread h1(esq1);
    thread h2(esq2);

    h1.join();
    h2.join();
    
   }
