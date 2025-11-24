import Jpmi.*;

public class Mesa implements Proceso {
    CanalSimple c1, c2, c3; // Canales de envío
    CanalSimple r1, r2, r3; // Canales de respuesta
    CanalSimple canalP4; // Canal para engrapador

    public Mesa(CanalSimple c1, CanalSimple c2, CanalSimple c3,
                CanalSimple r1, CanalSimple r2, CanalSimple r3,
                CanalSimple canalP4) {
        this.c1 = c1; 
        this.c2 = c2; 
        this.c3 = c3;
        this.r1 = r1; 
        this.r2 = r2; 
        this.r3 = r3;
        this.canalP4 = canalP4;
    }

    @Override
    public void run() {
        while(true) {
            c1.receive();
            c2.receive();
            c3.receive();

            canalP4.send(new Mensaje("Mesa", 3));  // Enviar a P4

            // Permitir que vuelvan a poner otra hoja
            r1.send(new Mensaje("Mesa", 0));
            r2.send(new Mensaje("Mesa", 0));
            r3.send(new Mensaje("Mesa", 0));
        }
    }
}
