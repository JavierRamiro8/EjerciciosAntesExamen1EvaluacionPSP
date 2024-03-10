package RepasoExamenMarzo.java.LectorEscritor;

public class Lector implements Runnable {

    @Override
    public void run() {
        while (true) {
            synchronized (MainLectorEscritor.lock) {
                if (MainLectorEscritor.detenerLectores) {
                    try {
                        MainLectorEscritor.lock.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
            if (MainLectorEscritor.libro.isEmpty()) {
                System.out.println("El hilo " + Thread.currentThread().getId() + " Esta leyendo este buen libro," +
                        "aunque ahora está vacío: " + MainLectorEscritor.libro);
            } else {
                System.out.println("El hilo " + Thread.currentThread().getId() + "Estamos leyendo este buen libro," +
                        "ahora estamos leyendo: " + MainLectorEscritor.libro);
            }

        }
    }
}