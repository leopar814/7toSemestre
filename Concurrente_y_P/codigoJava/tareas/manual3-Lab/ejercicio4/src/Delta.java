
import Jpmi.*;

public class Delta implements Proceso {

    CanalSimple canalIn, canalesOut[], canalesOutTemp[];
    Object dato;

    // Una entrada y varias salidas
    public Delta(CanalSimple canalIn, CanalSimple canalesOut[]) {
        this.canalIn = canalIn;
        this.canalesOut = canalesOut;
        canalesOutTemp = new CanalSimple[2];
        dato = null;
    }

    @Override
    public void run() {
        // while (true) {
            dato = canalIn.receive();
            int id = (Integer)dato;
            switch(id) {
                case 1: 
                    canalesOutTemp[0] = canalesOut[2];
                    canalesOutTemp[1] = canalesOut[3];
                    break;
                case 2: 
                    canalesOutTemp[0] = canalesOut[1];
                    canalesOutTemp[1] = canalesOut[3];
                    break;
                case 3: 
                    canalesOutTemp[0] = canalesOut[1];
                    canalesOutTemp[1] = canalesOut[2];
                    break;
            }
            Paralelo par = new Paralelo(new Proceso[]{
                new Escribe(true, canalesOutTemp[0]),
                new Escribe(true, canalesOutTemp[1]),
                new Escribe(dato, canalesOut[0]), 
            });
            par.run();
        }
    // }
}
