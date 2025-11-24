import Jpmi.*;

public class InCharsOutChar implements Proceso {

    CanalSimple canal_in1, canal_in2, canalOut;

    public InCharsOutChar(CanalSimple canal_in1, CanalSimple canal_in2, CanalSimple canalOut) {
        this.canal_in1 = canal_in1;
        this.canal_in2 = canal_in2;
        this.canalOut = canalOut;
    }

    @Override
    public void run() {

        while (true) {

            Lee l1 = new Lee(canal_in1);
            Lee l2 = new Lee(canal_in2);

            Paralelo lectura = new Paralelo(new Proceso[]{
                l1, l2
            });
            lectura.run();

            MiChar m1 = (MiChar) l1.getDato();
            MiChar m2 = (MiChar) l2.getDato();

            char c1 = m1.get();
            char c2 = m2.get();

            char salida = (c1 == '*' && c2 == '*') ? '#' : '$';

            canalOut.send(new MiChar(salida));
        }
    }
}
