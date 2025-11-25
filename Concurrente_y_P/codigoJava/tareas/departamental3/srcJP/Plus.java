import Jpmi.*;

public class Plus implements Proceso {
    CanalSimple canalIn1, canalIn2, canalOut;
    Integer num1, num2;
    
    public Plus(CanalSimple canalIn1, CanalSimple canalIn2, CanalSimple canalOut) {
        this.canalIn1 = canalIn1;
        this.canalIn2 = canalIn2;
        this.canalOut = canalOut;
        num1 = null;
        num2 = null;
    }
    
    @Override
    public void run() {
        while(true) {
            Lee lee1 = new Lee(canalIn1);
            Lee lee2 = new Lee(canalIn2);
            Paralelo par = new Paralelo(new Proceso[]{
               lee1,lee2
            });
            par.run();
            num1 = (Integer)lee1.getDato();
            num2 = (Integer)lee2.getDato();
            
            
            Integer suma = num1 + num2;
            canalOut.send(suma);
        }
    }
}