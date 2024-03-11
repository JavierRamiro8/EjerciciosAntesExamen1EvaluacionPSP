package RepasoExamenMarzo.java.GlobosDeAgua;

public class Ninios implements Runnable {
    private final int CONTADORDORMIDO=100;
    private static boolean fuenteLibre = true;
    @Override
    public void run() {
        while (true) {
            if (fuenteLibre) {
                fuenteLibre = false;
                fuente();
            } else {
                synchronized (MainGlobos.lock) {
                    try {
                        MainGlobos.lock.wait();
                    } catch (InterruptedException e) {
                    }
                }
            }
        }

    }

    public void fuente() {
        System.out.println(
                "ENTRA " + Thread.currentThread().getId() + "-RECARGA-SALE " + Thread.currentThread().getId());
        synchronized (MainGlobos.lock) {
            fuenteLibre = true;
            MainGlobos.lock.notifyAll();
        }
        try {
            Thread.sleep(CONTADORDORMIDO);
        } catch (InterruptedException e) {
        }
    }
}
