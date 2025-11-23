#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <random>

using namespace std;

mutex candado;

class X //MONITOR
   {
    public:
        int cont;

    public:

    	X(int cont)
    	   {
    	   	this->cont=cont;
    	   }

    	void incX(string id, string cad)
    	    {
           candado.lock();
    	        cont++;
              cout << id << cad << cont << "\n";
           candado.unlock();
    	    }

    	void decX(string id, string cad)
    	    {
           candado.lock();
    	        cont--; 	
              cout << id << cad << cont << "\n";
           candado.unlock();
    	    }

    	int getX()
    	   {
          int contador;

          candado.lock();
             contador=cont;
          candado.unlock();
    	    return contador;;
    	   }
   };


class Puerta
   {
    public:
   	   string id;
   	   X *cont;
   	   int estado;

   	public:
   	  Puerta(string id, X *cont)
   	     {
   	      srand(time(NULL));
   	      this->id=id;
   	      this->cont=cont;
   	     }

      void operator()()
         {
          for(;;)
            {
             estado=1 + rand() % (2 - 1 + 1);

             if(estado==1)
             	 { 
             	    if(cont->getX()<20)   
             		     cont->incX(id,"Ha entrado una persona a los Jardines...");
             	 }
             if(estado==2)
                {
                
                    if(cont->getX()!=0)
                        cont->decX(id, "Ha salido una persona a los Jardines...");
                }
            }
         }
   };

int main()
   {
   	X *cont=new X(0); 
   	Puerta p1("Puerta 1",cont);
   	Puerta p2("Puerta 2",cont);

   	thread h1(p1);
   	thread h2(p2);

   	h1.join();
   	h2.join();
   }