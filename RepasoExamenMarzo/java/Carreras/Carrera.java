package RepasoExamenMarzo.java.Carreras;

public class Carrera implements Runnable {
    private static final long TIEMPO_DESCANSO = 500;
    private static final double INTERVALO_KM = 10;
    private int kmRecorridos=0;
    private int kmTotales=100;

    int dorsal;
    
    public Carrera(int dorsal) {
        this.dorsal = dorsal;
    }

    @Override
    public void run() {
        synchronized(MainCarrera.lock){
            try {
                MainCarrera.lock.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println(String.format("Soy el dorsal %d, inicio mi carrera", dorsal));

        while (kmRecorridos < kmTotales) {
            try {
                System.out.println(String.format("Soy el dorsal %d, he recorrido %d KM de %d totales", dorsal,
                        kmRecorridos, kmTotales));
                long tiempoDeDescanso = (long) (Math.random() * TIEMPO_DESCANSO) + TIEMPO_DESCANSO;
                Thread.sleep(tiempoDeDescanso);
                System.out.println(String.format("Soy el dorsal %d, he descansado %d", dorsal, tiempoDeDescanso));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            kmRecorridos += Math.random() * INTERVALO_KM;
        }
        System.out.println(String.format("Soy el dorsal %d, TERMINE!!!", dorsal));
    }
    
}
