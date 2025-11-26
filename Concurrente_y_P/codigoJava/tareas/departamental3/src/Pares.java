import Jpmi.*;
public class Pares implements Proceso {
    CanalSimple canalIn, canalOut;
    Integer num;
    
    public Pares(CanalSimple canalIn, CanalSimple canalOut) {
        this.canalIn = canalIn;
        this.canalOut = canalOut;
        num = null;
    }
    
    @Override
    public void run(){
        while(true) {
            num=(Integer)canalIn.receive();
            
            Integer salida;
            
            if (num % 2 == 0) { // Par
                salida = num;
            } else {
                salida = num + 1; // Impar
            }

            canalOut.send(salida);
        }
    }  
}
