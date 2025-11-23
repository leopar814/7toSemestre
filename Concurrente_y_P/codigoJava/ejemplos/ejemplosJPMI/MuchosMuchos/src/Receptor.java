import Jpmi.*;

public class Receptor implements Proceso{
    CanalSimple canal[];
    Integer msg[];
    String id;
    
    public Receptor(String id, CanalSimple ...canal)
      {
       this.id=id;
       this.canal=canal;
       msg=new Integer[canal.length];
      }
    
    @Override
    public void run()
      {
        for(int i=0;i<msg.length; i++)
        {
         msg[i]=(Integer)canal[i].receive();
         System.out.println(id+" recibiendo el mensaje "+msg[i]+" del emisor "+(i+1));
        }
      }  
}
