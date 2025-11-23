
import Jpmi.*;

public class Emisor implements Proceso {
    CanalSimple canalOut;
    Integer msg;
   
    public Emisor(Integer msg, CanalSimple canalOut)
      {
       this.canalOut=canalOut;
       this.msg=msg;
      }
    
    @Override
    public void run()
      {
       System.out.print("Proceso EMISOR enviando "+msg+" al receptor...");
       canalOut.send(msg);
       System.out.println("Proceso EMISOR termina su ejecucion!!!");
      }
}
