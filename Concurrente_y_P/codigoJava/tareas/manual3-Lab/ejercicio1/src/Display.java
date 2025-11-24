import Jpmi.*;

public class Display implements Proceso {

    CanalSimple canalIn;
    
    public Display(CanalSimple canalIn) {
        this.canalIn = canalIn;
    }

    @Override
    public void run() {
        while (true) {
            MiChar c = (MiChar) canalIn.receive();
            System.out.println(c.get());
        }
    }
}