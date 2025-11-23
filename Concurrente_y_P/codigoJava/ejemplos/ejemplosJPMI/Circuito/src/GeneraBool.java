
import Jpmi.*;
public class GeneraBool implements Proceso {
    CanalSimple canalOut1, canalOut2, canalOut3;
    Integer dato1, dato2, dato3;
    
    public GeneraBool(Integer dato1, Integer dato2, Integer dato3, CanalSimple canalOut1, CanalSimple canalOut2, CanalSimple canalOut3){
        this.canalOut1=canalOut1;
        this.canalOut2=canalOut2;
        this.canalOut3=canalOut3;
        this.dato1=dato1;
        this.dato2=dato2;
        this.dato3=dato3;
    }
    
    @Override
    public void run(){
        Paralelo par=new Paralelo(new Proceso[]{
              new Escribe(dato1,canalOut1), 
              new Escribe(dato2,canalOut2),
              new Escribe(dato3,canalOut3)
        });
        par.run();
    }
}
