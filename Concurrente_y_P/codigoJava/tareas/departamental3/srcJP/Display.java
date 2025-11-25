import Jpmi.*;
public class Display implements Proceso {
    CanalSimple canalIn;
    Integer numero;
    int limite;
    int contador;

    public Display(int limite, CanalSimple canalIn) {
        this.canalIn = canalIn;
        numero = null;
        this.limite = limite;
        this.contador = 0;
    }

    @Override
    public void run() {
        
        while(true){
            numero = (Integer) canalIn.receive();
            
            System.out.println(numero);
            
            contador++;
            if (contador >= limite)
                break;
            
        }
        System.out.println(" ");
        System.exit(0);
    }
}
