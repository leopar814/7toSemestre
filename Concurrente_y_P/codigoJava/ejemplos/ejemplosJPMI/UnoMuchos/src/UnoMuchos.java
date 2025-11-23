
import Jpmi.*;
public class UnoMuchos {
    public static void main(String args[]){
        CanalSimple canal1=new CanalSimple();
        CanalSimple canal2=new CanalSimple();
        CanalSimple canal3=new CanalSimple();
        
        Alternativa alt=new Alternativa(new Guarda[]{
               new Guarda(true,new Receptor("1",canal1) ),
               new Guarda(false,new Receptor("2",canal2) ),
               new Guarda(true,new Receptor("3",canal3) ),
            
        });
        
        
        
        /*Secuencial seq=new Secuencial(new Proceso[]{
                        new Receptor("3",canal3),
                        new Receptor("2",canal2),
                        new Receptor("1",canal1)
                         
                        });*/
        
        Emisor emisor=new Emisor(100,alt,canal1,canal2,canal3);
        
        Paralelo par=new Paralelo(new Proceso[]{
                            emisor,
                            alt
        });
        
        par.run();
    }
}
