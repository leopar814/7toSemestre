import Jpmi.*;

public class Emisor implements Proceso {
    CanalSimple canal[];
    Integer msg;
    Alternativa alt;
   
    public Emisor(Integer msg, Alternativa alt, CanalSimple... canal)
      {
       this.canal=canal;
       this.msg=msg;
       this.alt=alt;
      }
    
    @Override
    public void run()
      {
       int indice=alt.select();
          
       if(indice==-1)
           System.exit(0);
       else {
           System.out.println("Proceso EMISOR enviando "+msg+" al receptor "+(indice+1));
           canal[indice].send(msg);
       }
       /*
       System.out.println("Proceso EMISOR enviando "+msg+" al receptor 3...");
       canal[2].send(msg);
       System.out.println("Proceso EMISOR enviando "+msg+" al receptor 2...");
       canal[1].send(msg);
       System.out.println("Proceso EMISOR enviando "+msg+" al receptor 1...");
       canal[0].send(msg);*/
       
       
       //System.out.println("Proceso EMISOR termina su ejecucion!!!");
      }
}
