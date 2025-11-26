import Jpmi.*;
public class main {
    public static void main(String args[]){
        CanalSimple a = new CanalSimple();
        CanalSimple b = new CanalSimple();
        CanalSimple c = new CanalSimple();
        CanalSimple d = new CanalSimple();
        CanalSimple e = new CanalSimple();
        CanalSimple f = new CanalSimple();
        CanalSimple g = new CanalSimple();
        CanalSimple h = new CanalSimple();
        CanalSimple i = new CanalSimple();
        
        Paralelo par=new Paralelo(new Proceso[]{
            new GeneraNaturales(a),
            new Delta(a,b,c),
            new Pares(b,d),
            new Impares(c,e),
            new Delta(e,g,h),
            new Prod(d,g,f),
            new Plus(f,h,i),
            new Display(100,i),
        });
        par.run();
    } 
}
