// 3 personas son encargadas de colocar c/u, una hoja de papel en su respectiva caja.
// Una cuarta persona está esperando a que las personas terminen de colocar sus hojas en las
// cajas para entonces hacer un conteo total de las hojas.
// La persona 1 colocará 50 hojas en su caja (una por una), 
// la persona 2 colocará 100 hojas en su caja (una por una) y 
// la persona 3 colocará 200 hojas en su caja (una por una).
#include <iostream>
#include <thread>

using namespace std;

int caja1 = 0, caja2 = 0, caja3 = 0;
int hojas = 0;

void persona1(){
    for(int i=0; i<50; i++){
        caja1++;
        cout << "Persona 1 colocando hoja..." << endl;
    }
}

void persona2(){
    for(int i=0; i<100; i++){
        caja2++;
        cout << "Persona 2 colocando hoja..." << endl;
    }
}

void persona3(){
    for(int i=0; i<200; i++){
        caja2++;
        cout << "Persona 3 colocando hoja..." << endl;
    }
}

void persona4(){
    cout << "\nPERSONA 4 CONTANDO HOJAS..." << endl;
    hojas = caja1 + caja2 + caja3;
}


int main() {
    thread hilo1(persona1);
    thread hilo2(persona2);
    thread hilo3(persona3);
    hilo1.join();
    hilo2.join();
    hilo3.join();
    
    thread hilo4(persona4);    
    hilo4.join();

    cout << "Total de hojas contadas: " << hojas << endl;

    return 0;
}