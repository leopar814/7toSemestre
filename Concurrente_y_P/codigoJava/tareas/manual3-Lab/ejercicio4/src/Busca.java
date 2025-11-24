
import Jpmi.*;

public class Busca implements Proceso {
    int[] nums;
    CanalSimple canalAviso;
    Integer id;

    public Busca(Integer id, int[] nums, CanalSimple canalAviso){
        this.nums = nums;
        this.canalAviso = canalAviso;
        this.id = id;
    }

    @Override
    public void run(){
        while(true){
            int sumaPares = 0;
            for(int n : nums){
                if(n % 2 == 0) sumaPares += n;
            }

            if(sumaPares == 70){
                canalAviso.send(id);
                break;
            }
        }
    }
}
