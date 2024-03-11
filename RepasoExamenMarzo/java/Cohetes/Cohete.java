package RepasoExamenMarzo.java.Cohetes;

public class Cohete implements Runnable {
    private final int DISTANCIAESTACION = 408;
    private final int DISTANCIARECORRIDA = 50;
    private final int TIEMPODORMIDOMAX = 1000;
    private final int TIEMPODORMIDOMIN = 500;
    private static int cohetesExplotados = 0;
    private final int EXPLOSION = 1;
    private final int MAXRANDNUM = 10;
    
    private int explotado;

    @Override
    public void run() {
        synchronized (MainCohetes.lock) {
            try {
                MainCohetes.lock.wait();
            } catch (InterruptedException e) {
            }
        }
        System.out.println("Soy el hilo " + Thread.currentThread().getId() + " empieza mi vuelo");
        int distanciaRecorrida = 0;
        while (distanciaRecorrida < DISTANCIAESTACION && explotado == 0) {
            distanciaRecorrida += DISTANCIARECORRIDA;
            if (distanciaRecorrida > DISTANCIAESTACION) {
                System.out.println("el hilo " + Thread.currentThread().getId() + " ha llegado a la estacion");
            } else {
                System.out.println("Soy el hilo" + Thread.currentThread().getId() + " y por ahora llevo "
                        + distanciaRecorrida + " km recorridos");
                int numeroAleatorioDormido = (int) ((Math.random() * TIEMPODORMIDOMAX) + TIEMPODORMIDOMIN);
                while (numeroAleatorioDormido > TIEMPODORMIDOMAX) {
                    numeroAleatorioDormido = (int) ((Math.random() * TIEMPODORMIDOMAX) + TIEMPODORMIDOMIN);
                }
                try {
                    Thread.sleep(numeroAleatorioDormido);
                } catch (InterruptedException e) {
                }
                explosion();
            }

        }
    }

    private synchronized void explosion() {
        int probabilidadExplosion = (int)(Math.random()*MAXRANDNUM+1);
        if (probabilidadExplosion == EXPLOSION) {
            cohetesExplotados++;
            System.out.println("El hilo " + Thread.currentThread().getId() + " ha explotado");
            Thread.currentThread().interrupt();
            explotado = 1;
        }
    }

    public static boolean estadoMision() {
        if (cohetesExplotados <= 3) {
            System.out.println("La mision a sido un exito");
            return true;
        } else {
            System.out.println("La mision ha sido un fracaso total, han explotado: "+cohetesExplotados);
            return false;
        }
    }
}
