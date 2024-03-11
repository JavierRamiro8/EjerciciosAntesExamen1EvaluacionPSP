package RepasoExamenMarzo.java.filosofos;

public class MainFilosofo {
    public static Object lock = new Object();

    public static void main(String[] args) {
        Filosofo filosofo1 = new Filosofo();
        Filosofo filosofo2 = new Filosofo();
        Filosofo filosofo3 = new Filosofo();
        Filosofo filosofo4 = new Filosofo();

        Thread filosofo1Thread = new Thread(filosofo1);
        Thread filosofo2Thread = new Thread(filosofo2);
        Thread filosofo3Thread = new Thread(filosofo3);
        Thread filosofo4Thread = new Thread(filosofo4);

        filosofo1Thread.start();
        filosofo2Thread.start();
        filosofo3Thread.start();
        filosofo4Thread.start();

        try {
            filosofo1Thread.join();
            filosofo2Thread.join();
            filosofo3Thread.join();
            filosofo4Thread.join();
        } catch (InterruptedException e) {
        }
    }
}
