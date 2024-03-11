package RepasoExamenMarzo.java.GlobosDeAgua;

public class MainGlobos {
    public static Object lock = new Object();

    public static void main(String[] args) {
        Ninios ninio1 = new Ninios();
        Ninios ninio2 = new Ninios();
        Ninios ninio3 = new Ninios();
        Thread ninio1Thread = new Thread(ninio1);
        Thread ninio2Thread = new Thread(ninio2);
        Thread ninio3Thread = new Thread(ninio3);

        ninio1Thread.start();
        ninio2Thread.start();
        ninio3Thread.start();

        try {
            ninio1Thread.join();
            ninio2Thread.join();
            ninio3Thread.join();

        } catch (InterruptedException e) {
        }

    }
}
