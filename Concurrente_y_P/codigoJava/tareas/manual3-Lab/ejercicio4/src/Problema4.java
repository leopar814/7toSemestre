import Jpmi.*;

public class Problema4 {
    public static void main(String args[]) {
        int[] nums = {10, 5, 12, 7, 8, 40};

        CanalSimple canalAviso = new CanalSimple(); // Muestreo en Display
        CanalSimple canalRecibido[] = new CanalSimple[4]; // Comprobación de condición cumplida

        for(int i = 0; i < canalRecibido.length; i++)
            canalRecibido[i] = new CanalSimple();
        // CanalSimple canalesAviso[] = new CanalSimple[6]; // Canales de aviso a los demás procesos

        // for (int i = 0; i < canalesAviso.length; i++)
        //     canalesAviso[i] = new CanalSimple();

        // // PARES son canales de SALIDA e IMPARES canales de ENTRADA
        // CanalSimple canalesProceso1[] = new CanalSimple[4];
        // canalesProceso1[0] = canalesAviso[0]; // Out
        // canalesProceso1[1] = canalesAviso[1]; // In
        // canalesProceso1[2] = canalesAviso[4]; // Out
        // canalesProceso1[3] = canalesAviso[5]; // In

        // CanalSimple canalesProceso2[] = new CanalSimple[4];
        // canalesProceso2[0] = canalesAviso[1]; // Out
        // canalesProceso2[1] = canalesAviso[0]; // In
        // canalesProceso2[2] = canalesAviso[2]; // Out
        // canalesProceso2[3] = canalesAviso[3]; // In

        // CanalSimple canalesProceso3[] = new CanalSimple[4];
        // canalesProceso3[0] = canalesAviso[3]; // Out
        // canalesProceso3[1] = canalesAviso[2]; // In
        // canalesProceso3[2] = canalesAviso[5]; // Out
        // canalesProceso3[3] = canalesAviso[4]; // In
    
        Paralelo par = new Paralelo(new Proceso[]{
            new Busca(1, nums, canalAviso, canalRecibido[1]),
            new Busca(2, nums, canalAviso, canalRecibido[2]),
            new Busca(3, nums, canalAviso, canalRecibido[3]),
            new Delta(canalAviso, canalRecibido),
            new Display(canalRecibido[0])
        });

        par.run();
    }
}
