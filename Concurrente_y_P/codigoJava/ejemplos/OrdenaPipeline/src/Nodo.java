
import Jpmi.*;

public class Nodo implements Proceso {

    CanalSimple canalIn, canalOut;
    Integer num, numtmp;

    public Nodo(CanalSimple canalIn, CanalSimple canalOut) {
        this.canalIn = canalIn;
        this.canalOut = canalOut;
        num = null;
        numtmp = null;
    }

    @Override
    public void run() {
        while (true) {
            numtmp = (Integer) canalIn.receive();
            if (num != null) {
                if (numtmp > num) {
                    canalOut.send(num);
                    num = numtmp;
                } else {
                    canalOut.send(numtmp);
                }
            }
            else num=numtmp;
        }
    }
}
