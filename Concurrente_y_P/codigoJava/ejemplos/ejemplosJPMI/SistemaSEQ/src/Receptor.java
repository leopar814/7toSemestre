
import Jpmi.*;

public class Receptor implements Proceso{
    CanalSimple canalIn;
    Integer msg;
    
    public Receptor(CanalSimple canalIn)
      {
       this.canalIn=canalIn;
       this.msg=null;
      }
    
    @Override
    public void run()
      {
       msg=(Integer)canalIn.receive();
       System.out.println("Proceso RECEPTOR recibiendo "+msg+" del emisor...");
       System.out.println("Proceso RECEPTOR termina su ejecucion!!!");
      }  
}
