
import Jpmi.*;

public class MuchosMuchos {
    public static void main(String args[]){
        
        CanalSimple canal[]=new CanalSimple[9];
        
        for(int i=0; i<canal.length;i++)
            canal[i]=new CanalSimple();
        
        Paralelo par=new Paralelo(new Proceso[]{
                         new Emisor("Emisor 1",10,canal[0],canal[1],canal[2]),
                         new Emisor("Emisor 2",50,canal[3],canal[4],canal[5]),
                         new Emisor("Emisor 3",100,canal[6],canal[7],canal[8]),
                         new Receptor("Receptor 1",canal[0],canal[3],canal[6]),
                         new Receptor("Receptor 2",canal[1],canal[4],canal[7]),
                         new Receptor("Receptor 3",canal[2],canal[5],canal[8]),
                         });
        par.run();       
    }
}
