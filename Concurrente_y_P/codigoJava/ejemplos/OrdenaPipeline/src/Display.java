
import Jpmi.*;
import java.util.Objects;

public class Display implements Proceso {

    CanalSimple canalIn;
    Integer num, centinela;

    public Display(Integer centinela, CanalSimple canalIn) {
        this.canalIn = canalIn;
        this.centinela = centinela;
        num = null;
    }

    @Override
    public void run() {
        while (true) {
            num = (Integer) canalIn.receive();
            if (Objects.equals(num, centinela)) {
                System.out.print("\n");
                System.exit(0);
            } else {
                System.out.print(num + ", ");
            }
        }
    }

}
