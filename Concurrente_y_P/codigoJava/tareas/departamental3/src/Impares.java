import Jpmi.*;
public class Impares implements Proceso {
    CanalSimple canalIn, canalOut;
    Integer num;
    
    public Impares(CanalSimple canalIn, CanalSimple canalOut) {
        this.canalIn = canalIn;
        this.canalOut = canalOut;
        num = null;
    }
    
    @Override
    public void run(){
        while(true) {
            num=(Integer)canalIn.receive();
            
            Integer salida;
            
            if (num % 2 != 0) {     // impar
                salida = num;
            } else {                // par
                salida = num + 1;
            }

            canalOut.send(salida);
        }
    }
}
