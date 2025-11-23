import Jpmi.*;

public class Display implements Proceso {
    CanalSimple canalIn;

    public Display(CanalSimple canalIn){
        this.canalIn = canalIn;
    }

    @Override
    public void run(){
        String quien = (String) canalIn.receive(); 
        System.out.println("La condicion la cumplio el " + quien + ": suma de pares = 70");
        System.exit(0);
    }
}
