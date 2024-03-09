package RepasoExamenMarzo.java.Fabrica;

public class Consumidores implements Runnable {
    private int numeroGeneradoAleatorio;

    private int extraerProductos() {
        numeroGeneradoAleatorio = (int) (Math.random() * 100);
        synchronized (MainFabrica.lock) {
            if ((MainFabrica.productosGenerados - numeroGeneradoAleatorio) >= 0) {
                MainFabrica.productosGenerados -= numeroGeneradoAleatorio;
            } else {
                numeroGeneradoAleatorio = MainFabrica.productosGenerados;
                MainFabrica.productosGenerados = 0;
            }
        }
        return numeroGeneradoAleatorio;
    }

    @Override
    public void run() {
        while (true) {
            int cantidadAExtraer = extraerProductos();
            if (cantidadAExtraer > 0) {
                System.out.println("Hemos sacado productos, "
                        + " En total tenemos: " + MainFabrica.productosGenerados);
                synchronized (MainFabrica.lock) {
                    MainFabrica.lock.notify();
                }
            } else {
                synchronized (MainFabrica.lock) {
                    try {
                        MainFabrica.lock.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }

    }

}
