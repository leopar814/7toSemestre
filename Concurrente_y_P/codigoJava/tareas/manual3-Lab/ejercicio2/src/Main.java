import Jpmi.*;

public class Main {
    public static void main(String[] args) {
        CanalSimple c1 = new CanalSimple();
        CanalSimple c2 = new CanalSimple();
        CanalSimple c3 = new CanalSimple();
        CanalSimple c4 = new CanalSimple();

        Paralelo par = new Paralelo(new Proceso[]{
                new Nodo("Nodo 1",c1 , c2, true),
                new Nodo("Nodo 2",c2 , c3, false),
                new Nodo("Nodo 3",c3 , c4, false),
                new Nodo("Nodo 4",c4 , c1, false),
        });
        par.run();
    }
}