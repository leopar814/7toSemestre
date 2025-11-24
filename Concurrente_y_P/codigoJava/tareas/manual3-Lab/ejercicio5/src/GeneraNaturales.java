import Jpmi.*;

public class GeneraNaturales implements Proceso{
    CanalSimple canalOut;
    
    public GeneraNaturales(CanalSimple canalOut){
        this.canalOut = canalOut;
    }
    
    @Override
    public void run(){
        CanalSimple c1=new CanalSimple();
        CanalSimple c2=new CanalSimple();
        CanalSimple c3=new CanalSimple();
        CanalSimple c4=new CanalSimple();
        
        Paralelo par=new Paralelo(new Proceso[]{
              new Prefijo(0,c4,c1),
              new Delta(c1,c2,c3),
              new Id(c2,canalOut),
              new Suc(c3,c4)
        });
        par.run();
    }
    
}
