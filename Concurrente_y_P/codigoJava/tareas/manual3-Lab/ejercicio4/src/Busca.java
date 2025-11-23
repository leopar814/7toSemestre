
import Jpmi.*;

public class Busca implements Proceso {
    int[] nums;
    CanalSimple canalAviso;
    CanalSimple canalRecibido;
    int id;

    public Busca(int id, int[] nums, CanalSimple canalAviso, CanalSimple canalRecibido){
        this.nums = nums;
        this.canalAviso = canalAviso;
        this.canalRecibido = canalRecibido;
        this.id = id;
    }

    @Override
    public void run(){
        while(true){
            int sumaPares = 0;
            for(int n : nums){
                if(n % 2 == 0) sumaPares += n;
            }

            if (comprobarDemasProcesos()) {
                System.out.print("Proceso " + id + " terminando ejecución");
                break;
            }
            
            if(sumaPares == 70) {
                avisar();
                break;
            }
        }
    }

    private boolean comprobarDemasProcesos() {
        Lee leeComprobacion = new Lee(canalRecibido);
        leeComprobacion.run();

        boolean condicionEncontrada = (Boolean)leeComprobacion.getDato();

        if(condicionEncontrada)
            return true;

        return false;
    }

    private void avisar() {
        canalAviso.send(id);
    }
}