
#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>
#include <random>

using namespace std;

mutex candado;

class X
   {
    public:
        int cont;

    public:

    	X(int cont)
    	   {
    	   	this->cont=cont;
    	   }

    	void incX()
    	    {
    	     cont++;
    	    }

    	void decX()
    	    {
    	     cont--; 	
    	    }

    	int getX()
    	   {
    	   	return cont;
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
             	  candado.lock();
             	    if(cont->getX()<20)
                       {
             		cont->incX();
             		cout << id << "Ha entrado una persona a los Jardines..." << cont->getX() << "\n";
             	}
             	  candado.unlock();
             	 }
             if(estado==2)
                {
                 candado.lock();
                    if(cont->getX()!=0)
                       {
                        cont->decX();
             		cout << id << "Ha salido una persona a los Jardines..." << cont->getX() << "\n";
                       }
             	  candado.unlock();
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