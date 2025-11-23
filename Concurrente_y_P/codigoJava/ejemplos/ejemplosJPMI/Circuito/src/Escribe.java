
import Jpmi.*;

public class Escribe implements Proceso{
    CanalSimple canalOut;
    Object dato;
    
    public Escribe(Object dato,CanalSimple canalOut){
        this.canalOut=canalOut;
        this.dato=dato;
    }
    
    @Override
    public void run(){
        canalOut.send(dato);
    }
}
