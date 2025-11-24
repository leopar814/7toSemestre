import Jpmi.*;

public class main {

    public static void main(String[] args) {

        CanalSimple canalEntradaAlimentador = new CanalSimple();  
        CanalSimple canalSalida1Alimentador = new CanalSimple();
        CanalSimple canalSalida2Alimentador = new CanalSimple();

        CanalSimple canalSalidaFiltro = new CanalSimple(); 

        Alimentador alimentador = new Alimentador(
                canalEntradaAlimentador, 
                canalSalida1Alimentador, 
                canalSalida2Alimentador
        );

        InCharsOutChar filtro = new InCharsOutChar(
                canalSalida1Alimentador, 
                canalSalida2Alimentador, 
                canalSalidaFiltro
        );

        Display display = new Display(canalSalidaFiltro);

        //Generador de caracteres
        new Thread(() -> {
            char[] datos = {'*', '*', 'x', '*', '*', 'a', '*', '*', '-', '*', '*'};
            int i = 0;
            while (true) {
                canalEntradaAlimentador.send(new MiChar(datos[i % datos.length]));
                i++;
                try { Thread.sleep(300); } catch (Exception e) {}
            }
        }).start();

        Paralelo par = new Paralelo(new Proceso[]{
            alimentador,
            filtro,
            display
        });

        par.run();
    }
}
