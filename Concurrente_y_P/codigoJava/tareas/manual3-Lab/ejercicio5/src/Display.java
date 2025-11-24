import Jpmi.*;
public class Display implements Proceso {
    CanalSimple canalIn;
    Integer numero;
    int limite;

    public Display(int limite, CanalSimple canalIn) {
        this.canalIn = canalIn;
        numero = null;
        this.limite = limite;
    }

    @Override
    public void run() {
        
        while(true){
            numero = (Integer) canalIn.receive();
            if(numero >= limite){
                break;
            }
            System.out.print(numero+" ");
        }
        System.out.println(" ");
        System.exit(0);
    }
}
