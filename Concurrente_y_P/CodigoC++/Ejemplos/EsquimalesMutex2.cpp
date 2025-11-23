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
        
        void pescar(string id, int contadorPeces)
           {
            candado.lock();
           	
            cout << id << " Ha pescado: " << contadorPeces << "peces" << "QUEDAN " << numPeces << "peces\n";
            numPeces--;
            candado.unlock();
           }

    	int getPeces()
    	   {
            int totalPeces;

            candado.lock();
               totalPeces=numPeces;
            candado.unlock();
    	   	return totalPeces;
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
          	 
          	 if (hoyo->getPeces()>0)
          	     {
                  contadorPeces++;
                  hoyo->pescar(id,contadorPeces);
                  
                 // cout << id << " Ha pescado: " << contadorPeces << "peces" << "QUEDAN " << hoyo->getPeces() << "peces\n";
          	     }
          	  else {
          	        
                    
                         break;
          	       } 
          	}
         candado.unlock();
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
