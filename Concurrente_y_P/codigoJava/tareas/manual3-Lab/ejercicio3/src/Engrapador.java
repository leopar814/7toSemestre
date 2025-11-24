import Jpmi.*;

public class Engrapador implements Proceso {
    CanalSimple canal;

    public Engrapador(CanalSimple canal) {
        this.canal = canal;
    }

    @Override
    public void run() {
        while(true) {
            Mensaje msg = (Mensaje) canal.receive();
            System.out.println("P4 engrapando " + msg.dato + " hojas");
        }
    }
}
