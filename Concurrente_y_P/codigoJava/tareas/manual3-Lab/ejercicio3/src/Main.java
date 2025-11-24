import Jpmi.*;

public class Main {
    public static void main(String args[]) {
        // Canales de envío
        CanalSimple c1 = new CanalSimple();
        CanalSimple c2 = new CanalSimple();
        CanalSimple c3 = new CanalSimple();

        // Canales de respuesta
        CanalSimple r1 = new CanalSimple();
        CanalSimple r2 = new CanalSimple();
        CanalSimple r3 = new CanalSimple();

        CanalSimple c4 = new CanalSimple(); // Mesa → P4

        Paralelo par = new Paralelo(new Proceso[] {
            new Persona("P1", c1, r1),
            new Persona("P2", c2, r2),
            new Persona("P3", c3, r3),

            new Mesa(c1, c2, c3, r1, r2, r3, c4),

            new Engrapador(c4)
        });

        par.run();
    }
}
