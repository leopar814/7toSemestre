import Jpmi.*;

public class Lee implements Proceso {
    CanalSimple canalIn;
    Object dato;
    
    public Lee(CanalSimple canalIn){
        this.canalIn=canalIn;
        dato=null;
    }
    
    @Override
    public void run(){
        dato=canalIn.receive();
    }
    
    public Object getDato(){
        return dato;
    }
}
