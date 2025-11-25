import Jpmi.*;

public class Generador implements Proceso {

    CanalSimple canalSalida;

    public Generador(CanalSimple canalSalida) {
        this.canalSalida = canalSalida;
    }

    @Override
    public void run() {
        char[] datos = {'*', '*', 'x', '*', '*', 'a', '*', '*', '-', '*', '*'};

        int i = 0;

        while (true) {
            canalSalida.send(new MiChar(datos[i % datos.length]));
            i++;
        }
    }
}
