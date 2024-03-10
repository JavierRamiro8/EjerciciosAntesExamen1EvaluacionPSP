package RepasoExamenMarzo.java.LectorEscritor;

import java.util.Scanner;

public class Escritor implements Runnable {

    @Override
    public void run() {
        Scanner in = new Scanner(System.in);
        while (true) {
            synchronized (MainLectorEscritor.lock) {
                System.out.println("Ahora Esperad, estoy escribiendo");
                MainLectorEscritor.libro=in.nextLine();
                System.out.println("Proseguid, me voy a dormir");

                MainLectorEscritor.detenerLectores = true;
                MainLectorEscritor.lock.notifyAll();
                MainLectorEscritor.detenerLectores = false;
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        } 
    }

}
