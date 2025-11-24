import Jpmi.*;

public class Persona implements Proceso {
    CanalSimple canalEnvio;
    CanalSimple canalRespuesta;
    String nombre;

    public Persona(String nombre, CanalSimple canalEnvio, CanalSimple canalRespuesta) {
        this.nombre = nombre;
        this.canalEnvio = canalEnvio;
        this.canalRespuesta = canalRespuesta;
    }

    @Override
    public void run() {
        while(true) {
            System.out.println(nombre + " poniendo 1 hoja en la mesa");
            canalEnvio.send(new Mensaje(nombre, 1));  // Envía hoja

            // Espera permiso de la Mesa
            canalRespuesta.receive();
        }
    }
}


