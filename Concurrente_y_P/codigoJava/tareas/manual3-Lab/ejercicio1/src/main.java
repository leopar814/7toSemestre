import Jpmi.*;

public class main {

    public static void main(String[] args) {

        // Canales para el Alimentador
        CanalSimple canalEntradaAlimentador = new CanalSimple();  
        CanalSimple canalSalida1Alimentador = new CanalSimple();
        CanalSimple canalSalida2Alimentador = new CanalSimple();

        CanalSimple canalSalidaFiltro = new CanalSimple(); 

        // Procesos
        Generador generador = new Generador(canalEntradaAlimentador);
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

        Paralelo par = new Paralelo(new Proceso[]{
            generador,
            alimentador,
            filtro,
            display
        });

        par.run();
    }
}

