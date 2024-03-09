package RepasoExamenMarzo.java.Carreras;

public class MainCarrera {
    public static Object lock = new Object();

    public static void main(String[] args) {
        Thread[] hilo = new Thread[20];
        Carrera[] corredor = new Carrera[20];
        for (int i = 0; i < corredor.length; i++) {
            int dorsal = (int) (Math.random() * 100);
            corredor[i] = new Carrera(dorsal);
            hilo[i] = new Thread(corredor[i]);
        }
        for (int i = 0; i < hilo.length; i++) {
            hilo[i].start();
        }
        synchronized (lock) {
            lock.notifyAll();
        }

        
        for (int i = 0; i < hilo.length; i++) {
            try {
                hilo[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

    }
}
