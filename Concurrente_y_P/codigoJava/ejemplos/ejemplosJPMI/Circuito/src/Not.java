
import Jpmi.*;

public class Not implements Proceso {
    CanalSimple canalIn, canalOut;
    Integer valorInBool, valorOutBool;
    
    public Not(CanalSimple canalIn, CanalSimple canalOut){
        this.canalIn=canalIn;
        this.canalOut=canalOut;
        valorInBool=null;
        valorOutBool=null;
    }
    
    @Override
    public void run(){
        valorInBool=(Integer)canalIn.receive();
        if(valorInBool==0)
            valorOutBool=1;
        else valorOutBool=0;
        canalOut.send(valorOutBool);
    } 
}
