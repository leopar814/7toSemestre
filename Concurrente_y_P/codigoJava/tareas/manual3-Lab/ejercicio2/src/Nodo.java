import Jpmi.*;

public class Nodo implements Proceso {
    CanalSimple canalIn, canalOut;
    Object dato;
    String id;
    boolean centinela;

    public Nodo(String id, CanalSimple canalIn, CanalSimple canalOut, boolean centinela) {
        this.canalIn = canalIn;
        this.canalOut = canalOut;
        this.id = id;
        this.centinela = centinela;
        this.dato = null;
    }

    @Override
    public void run(){
        while(true) {
            if(centinela) {
                if(dato == null) {
                    dato = (int)(Math.random()*100)+1;
                    System.out.println(id + " envia: " + dato);
                    canalOut.send(dato);
                }else{
                    dato = canalIn.receive();
                    System.out.println(id + " recibe: " + dato);
                    System.out.println(" ");
                    dato = (int)(Math.random()*100)+1;
                    System.out.println(id + " envia: " + dato);
                    canalOut.send(dato);
                }
            }
            else {
                dato = canalIn.receive();
                System.out.println(id + " recibe: " + dato + ", envia: " + dato);
                canalOut.send(dato);
            }
        }
    }
}
