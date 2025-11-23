import Jpmi.*;

public class Emisor implements Proceso {
    CanalSimple canal[];
    Integer msg;
    String id;
    
   
    public Emisor(String id,Integer msg,CanalSimple ...canal)
      {
       this.id=id;
       this.canal=canal;
       this.msg=msg;
      }
    
    @Override
    public void run()
      {
        for(int i=0;i<canal.length;i++)
        {
         System.out.println(id+" enviando "+msg+" al receptor "+(i+1));
           canal[i].send(msg);   
        }
      }
}
