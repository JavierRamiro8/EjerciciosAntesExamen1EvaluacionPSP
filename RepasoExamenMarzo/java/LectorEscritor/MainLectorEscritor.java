package RepasoExamenMarzo.java.LectorEscritor;

public class MainLectorEscritor {
    public static String libro = "";
    public static Object lock = new Object();
    public static boolean detenerLectores=false;

    public static void main(String[] args) {
        Lector primerLector = new Lector();
        Thread lectorPrimario = new Thread(primerLector);
        Lector segundoLector = new Lector();
        Thread lectorSecundario = new Thread(segundoLector);
        Escritor escriba = new Escritor();
        Thread escritor = new Thread(escriba);

        lectorPrimario.start();
        lectorSecundario.start();
        escritor.start();

        try {
            lectorPrimario.join();
            lectorSecundario.join();
            escritor.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
