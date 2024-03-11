package RepasoExamenMarzo.java.Cohetes;

/* */
public class MainCohetes {
    public static Object lock = new Object();

    public static void main(String[] args) {
        int numeroCohetes = Integer.parseInt(args[0]);
        if (numeroCohetes == 0 || numeroCohetes < 0) {
            System.out.println("Argumentos insuficientes");
        } else {
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
}