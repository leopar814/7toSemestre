import Jpmi.*;

public class Circuito {
    public static void main(String args[]){
        CanalSimple a=new CanalSimple();
        CanalSimple b=new CanalSimple();
        CanalSimple c=new CanalSimple();
        CanalSimple d=new CanalSimple();
        CanalSimple e=new CanalSimple();
        CanalSimple f=new CanalSimple();
        CanalSimple g=new CanalSimple();
        CanalSimple x1=new CanalSimple();
        CanalSimple x2=new CanalSimple();
        CanalSimple y1=new CanalSimple();
        CanalSimple y2=new CanalSimple();
        
        Paralelo par=new Paralelo(new Proceso[]{
            new GeneraBool(1,1,1,a,b,c),
            new Delta(a,x1,x2),
            new Delta(b,y1,y2),
            new And(x1,y2,d),
            new Not(x2,e),
            new Or(e,c,f),
            new And(d,f,g),
            new Display(y1,g)
        });
        par.run();
    }
    
}
