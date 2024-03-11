package RepasoExamenMarzo.java.filosofos;

public class Filosofo implements Runnable {
    private boolean tenedorIzq = true;
    private boolean tenedorDrch = true;

    private void comer() {
        System.out.println("soy el filosofo " + Thread.currentThread().getId() + " Estoy comiendo");
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
        }
        System.out.println("soy el filosofo " + Thread.currentThread().getId() + " termine de comer");
        tenedorIzq = true;
        tenedorDrch = true;
        synchronized (MainFilosofo.lock) {
            MainFilosofo.lock.notifyAll();
        }
    }

    @Override
    public void run() {
        while (true) {
            if (tenedorIzq && tenedorDrch) {
                tenedorIzq = false;
                tenedorDrch = false;
                comer();
            } else {
                synchronized (MainFilosofo.lock) {
                    try {
                        MainFilosofo.lock.wait();
                    } catch (InterruptedException e) {
                    }
                }
            }
        }
    }

}
