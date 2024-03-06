package RepasoExamenMarzo.java;

public class MainCuentaBancaria {
    private static final int CANTIDADRETIRADA=50;
    private static final int CANTIDADINGRESADA=100;
    public static Object lock; // Objeto compartido para la sincronización
    public static void main(String[] args) {
        CuentaBancaria cuenta = new CuentaBancaria();
        lock=new Object();
        Thread retirada = new Thread(() -> {
            synchronized (lock) {
                cuenta.retirar(CANTIDADRETIRADA);
                System.out.println("Dinero despues de retirar en la cuenta disponible " + cuenta.getSaldo());
                lock.notify();
            }
        });

        Thread ingreso = new Thread(() -> {
            synchronized (lock) {
                    try {
                        lock.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                
                cuenta.depositar(CANTIDADINGRESADA);
                System.out.println("Dinero en la cuenta disponible " + cuenta.getSaldo());
            }
        });

        try {
            ingreso.start();
            retirada.start();

            retirada.join();
            ingreso.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Dinero final en la cuenta " + cuenta.getSaldo());
    }
} 