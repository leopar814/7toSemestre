
import Jpmi.*;

public class Display implements Proceso {
      CanalSimple canal1In, canal2In;
      Integer datoBool1, datoBool2;
      
      public Display(CanalSimple canal1In, CanalSimple canal2In){
          this.canal1In=canal1In;
          this.canal2In=canal2In;
          datoBool1=datoBool2=null;
      }
      
      @Override
      public void run(){
          Lee lee1=new Lee(canal1In);
          Lee lee2=new Lee(canal2In);
          
          Paralelo par=new Paralelo(new Proceso[]{
              lee1, lee2
          });
          
          par.run();
          datoBool1=(Integer)lee1.getDato();
          datoBool2=(Integer)lee2.getDato();
          System.out.println(datoBool1+", "+datoBool2);
          System.exit(0);
      }
}
