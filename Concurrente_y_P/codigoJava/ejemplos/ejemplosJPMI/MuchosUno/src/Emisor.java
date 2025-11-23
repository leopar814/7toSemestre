import Jpmi.*;

public class Emisor implements Proceso {
    CanalSimple canalOut;
    Integer msg;
    String id;
    
   
    public Emisor(String id,Integer msg,CanalSimple canalOut)
      {
       this.id=id;
       this.canalOut=canalOut;
       this.msg=msg;
      }
    
    @Override
    public void run()
      {
           System.out.println(id+" enviando "+msg+" al receptor ");
           canalOut.send(msg);
      }
}

