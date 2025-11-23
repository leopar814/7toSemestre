
import Jpmi.*;

public class SistemaSEQ {
    public static void main(String args[]){
        CanalSimple canal=new CanalSimple();
        
        Alternativa alt=new Alternativa(new Guarda[]{
                          new Guarda(true,new Emisor(100,canal)),
                          new Guarda(true,new Receptor(canal)) 
        });
        alt.run();
    }
}
