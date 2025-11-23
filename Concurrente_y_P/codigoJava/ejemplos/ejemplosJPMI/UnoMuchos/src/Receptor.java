import Jpmi.*;

public class Receptor implements Proceso{
    CanalSimple canalIn;
    Integer msg;
    String id;
    
    public Receptor(String id, CanalSimple canalIn)
      {
       this.id=id;
       this.canalIn=canalIn;
       this.msg=null;
      }
    
    @Override
    public void run()
      {
       msg=(Integer)canalIn.receive();
       System.out.println("Proceso RECEPTOR "+id+" recibiendo "+msg+" del emisor...");
       //System.out.println("Proceso RECEPTOR termina su ejecucion!!!");
      }  
}
