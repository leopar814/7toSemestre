import Jpmi.*;

public class Integrador {
    public static void main(String args[]){
        CanalSimple a = new CanalSimple();
        CanalSimple b = new CanalSimple();
        CanalSimple c = new CanalSimple();
        CanalSimple in = new CanalSimple();
        CanalSimple out = new CanalSimple();
        
        Paralelo par=new Paralelo(new Proceso[]{
            new GeneraNaturales(in),  
            new Plus(in,a,b),
            new Delta(b,c,out),
            new Display(200,out),
            new Prefijo(0,c,a)
        });
        par.run();
    } 
}
