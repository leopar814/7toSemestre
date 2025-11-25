import Jpmi.*;

public class GeneraNaturales {
    public static void main(String args[]){
        CanalSimple c1=new CanalSimple();
        CanalSimple c2=new CanalSimple();
        CanalSimple c3=new CanalSimple();
        CanalSimple c4=new CanalSimple();
        
        Paralelo par=new Paralelo(new Proceso[]{
              new Prefijo(0,c4,c1),
              new Delta(c1,c2,c3),
              new Display(100,c2),
              new Suc(c3,c4)
        });
        par.run();
    }
    
}
