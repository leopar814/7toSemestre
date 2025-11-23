
import Jpmi.*;
import java.util.*;

public class Generador implements Proceso {

    CanalSimple canalOut;
    Integer nums[], centinela, n;

    public Generador(int n, int centinela, CanalSimple canalOut) {
        this.canalOut = canalOut;
        this.centinela = centinela;
        this.n = n;
        nums = new Integer[n];
        for (int i = 0; i < n; i++) {
            nums[i] = (int) (Math.random() * 100) + 1;
            System.out.print(nums[i]+", ");
        }
        System.out.print("\n");
    }

    @Override
    public void run() {
        int i = 0;
        while (true) {
            if (i < n) {
                canalOut.send(nums[i]);
                i++;
            } else {
                canalOut.send(centinela);
            }
        }
    }

}
