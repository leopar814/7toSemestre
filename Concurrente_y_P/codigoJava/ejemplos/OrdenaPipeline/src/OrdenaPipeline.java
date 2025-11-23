
import Jpmi.*;

public class OrdenaPipeline {
    public static void main(String args[]){
        CanalSimple c1=new CanalSimple();
        CanalSimple c2=new CanalSimple();
        CanalSimple c3=new CanalSimple();
        CanalSimple c4=new CanalSimple();
        CanalSimple c5=new CanalSimple();
        CanalSimple c6=new CanalSimple();
        
        Paralelo par=new Paralelo(new Proceso[]{
            new Generador(5,1000,c1),
            new Nodo(c1,c2),
            new Nodo(c2,c3),
            new Nodo(c3,c4),
            new Nodo(c4,c5),
            new Nodo(c5,c6),
            new Display(1000,c6)    
        });
        par.run();
    }
}
