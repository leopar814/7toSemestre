import Jpmi.*;
public class MuchosUno {
    public static void main(String args[]){
        CanalSimple canal1=new CanalSimple();
        CanalSimple canal2=new CanalSimple();
        CanalSimple canal3=new CanalSimple();
        
        Alternativa alt=new Alternativa(new Guarda[]{
                     new Guarda(true,new Emisor("Emisor 1",10,canal1)),
                     new Guarda(true,new Emisor("Emisor 2",20,canal2)),
                     new Guarda(true,new Emisor("Emisor 3",30,canal3)),
                    });
        
        
        /*Secuencial seq=new Secuencial(new Proceso[]{
                              new Emisor("Emisor 3",30,canal3),
                              
                              new Emisor("Emisor 1",10,canal1),
                              new Emisor("Emisor 2",20,canal2)
                             });*/
        Receptor receptor=new Receptor("RECEPTOR",alt,canal1,canal2,canal3);
        
        Paralelo par=new Paralelo(new Proceso[]{
                     alt,
                     receptor
                            
        });
        
        par.run();
    }
}
