import Jpmi.*;

public class Busca implements Proceso {
    int[] nums;
    CanalSimple canalAviso;
    String nombre;

    public Busca(String nombre, int[] nums, CanalSimple canalAviso){
        this.nums = nums;
        this.canalAviso = canalAviso;
        this.nombre = nombre;
    }

    @Override
    public void run(){
        while(true){
            int sumaPares = 0;
            for(int n : nums){
                if(n % 2 == 0) sumaPares += n;
            }

            if(sumaPares == 70){
                canalAviso.send(nombre);
                break;
            }
        }
    }
}

