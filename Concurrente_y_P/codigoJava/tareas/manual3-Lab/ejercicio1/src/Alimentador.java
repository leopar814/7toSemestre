
import Jpmi.*;

public class Alimentador implements Proceso {

    CanalSimple canalIn, canalOut1, canalOut2;

    public Alimentador(CanalSimple canalIn, CanalSimple canalOut1, CanalSimple canalOut2) {
        this.canalIn = canalIn;
        this.canalOut1 = canalOut1;
        this.canalOut2 = canalOut2;
    }

    @Override
    public void run() {
        while (true) {
           MiChar dato = (MiChar)canalIn.receive();
            Paralelo par = new Paralelo(new Proceso[]{
                new Escribe(dato, canalOut1),
                new Escribe(dato, canalOut2)
            });
            par.run();
        }
    }
}
