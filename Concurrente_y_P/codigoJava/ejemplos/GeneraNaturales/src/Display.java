
import Jpmi.*;

public class Display implements Proceso {

    CanalSimple canalIn;
    Integer numero;
    int limite;

    public Display(int limite, CanalSimple canalIn) {
        this.canalIn = canalIn;
        numero = null;
        this.limite = limite;
    }

    @Override
    public void run() {
        for (int i = 1; i <= limite; i++) {
            numero = (Integer) canalIn.receive();
            System.out.println(numero);
        }
        System.exit(0);
    }
}
