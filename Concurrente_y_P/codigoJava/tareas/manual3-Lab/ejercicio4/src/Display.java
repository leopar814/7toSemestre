import Jpmi.*;

public class Display implements Proceso {
    CanalSimple canalIn;

    public Display(CanalSimple canalIn){
        this.canalIn = canalIn;
    }

    @Override
    public void run(){
        int procesoGanador = (Integer)canalIn.receive(); 
        int procesoA, procesoB; 
        switch (procesoGanador) {
            case 1:
                procesoA = 2;
                procesoB = 3;
                break;
            case 2:
                procesoA = 1;
                procesoB = 3;
                break;
            case 3:
                procesoA = 1;
                procesoB = 2;
                break;
        
            default:
                procesoA = -1;
                procesoB = -1;
                break;
        }
        System.out.println("Proceso " + procesoGanador + " cumplió la condición: Suma de pares = 70");
        System.out.println("Proceso " + procesoA + " termina su ejecución");
        System.out.println("Proceso " + procesoB + " termina su ejecución");
        System.exit(0);
    }
}
