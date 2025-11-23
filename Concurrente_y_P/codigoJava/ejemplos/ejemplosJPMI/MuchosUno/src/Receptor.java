import Jpmi.*;

public class Receptor implements Proceso{
    CanalSimple canal[];
    Integer msg;
    String id;
    Alternativa alt;
    
    public Receptor(String id, Alternativa alt, CanalSimple ...canal)
      {
       this.id=id;
       this.canal=canal;
       this.msg=null;
       this.alt=alt;
      }
    
    @Override
    public void run()
      {
        int indice=alt.select();
        if(indice==-1)
            System.exit(0);
        else {
              msg=(Integer)canal[indice].receive();
              System.out.println(id+" recibiendo "+msg+" del emisor "+(indice+1));
             }
        
        
        /*
        msg=(Integer)canal[2].receive();
        System.out.println(id+" recibiendo "+msg+" del emisor3...");
         msg=(Integer)canal[0].receive();
        System.out.println(id+" recibiendo "+msg+" del emisor1...");
        msg=(Integer)canal[1].receive();
        System.out.println(id+" recibiendo "+msg+" del emisor2...");*/
       
        
       
      }  
}
