import Jpmi.*;
public class Or implements Proceso {
    CanalSimple canalIn1, canalIn2, canalOut;
    Integer valorIn1Bool, valorIn2Bool, valorOutBool;
    
    public Or(CanalSimple canalIn1, CanalSimple canalIn2, CanalSimple canalOut){
        this.canalIn1=canalIn1;
        this.canalIn2=canalIn2;
        this.canalOut=canalOut;
        valorIn1Bool=valorIn2Bool=valorOutBool=null;
    }
    
    public void run(){
        
        Lee lee1=new Lee(canalIn1);
        Lee lee2=new Lee(canalIn2);
        
        Paralelo par=new Paralelo(new Proceso[]{
               lee1, lee2 
        });
        par.run();
        valorIn1Bool= (Integer)lee1.getDato();
        valorIn2Bool= (Integer)lee2.getDato();
        
        if((valorIn1Bool==0)&&(valorIn2Bool==0))
            valorOutBool=0;
        else valorOutBool=1;
        canalOut.send(valorOutBool);
    }
}
