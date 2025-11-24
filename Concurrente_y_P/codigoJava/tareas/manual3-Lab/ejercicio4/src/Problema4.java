
import Jpmi.*;

public class Problema4 {
    public static void main(String args[]) {
        int[] numeros = {10, 5, 12, 7, 8, 40};
        CanalSimple canalAviso = new CanalSimple();

        Paralelo par = new Paralelo(new Proceso[]{
            new Busca(1, numeros, canalAviso),
            new Busca(2, numeros, canalAviso),
            new Busca(3, numeros, canalAviso),
            new Display(canalAviso)
        });

        par.run();
    }
}
