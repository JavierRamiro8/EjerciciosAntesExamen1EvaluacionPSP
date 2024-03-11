package RepasoExamenMarzo.java.Cohetes;

/*Integer.parseInt(args[0]); */
public class MainCohetes {
    public static Object lock = new Object();

    public static void main(String[] args) {
        int numeroCohetes = 4;
        Cohete cohetes[] = new Cohete[numeroCohetes];
        Thread coheteHilos[] = new Thread[numeroCohetes];
        for (int i = 0; i < numeroCohetes; i++) {
            cohetes[i] = new Cohete();
            coheteHilos[i] = new Thread(cohetes[i]);
        }
        for (int i = 0; i < numeroCohetes; i++) {
            coheteHilos[i].start();
        }
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        synchronized (lock) {
            lock.notifyAll();
        }
        for (int i = 0; i < numeroCohetes; i++) {
            try {
                coheteHilos[i].join();
            } catch (InterruptedException e) {
            }
        }
        Cohete.estadoMision();
    }
}