package RepasoExamenMarzo.java.Fabrica;

public class Productores implements Runnable {
    private int numeroGeneradoAleatorio;

    private int generarProductos() {
        numeroGeneradoAleatorio = (int) (Math.random() * 100);
        synchronized (MainFabrica.lock) {
            if ((MainFabrica.productosGenerados + numeroGeneradoAleatorio) <= MainFabrica.productosGeneradosMaximo) {
                MainFabrica.productosGenerados += numeroGeneradoAleatorio;
            } else {
                numeroGeneradoAleatorio = MainFabrica.productosGeneradosMaximo - MainFabrica.productosGenerados;
                MainFabrica.productosGenerados = MainFabrica.productosGeneradosMaximo;
            }
        }
        return numeroGeneradoAleatorio;
    }

    @Override
    public void run() {
        while (true) {
            int cantidadGenerada = generarProductos();
            if (cantidadGenerada > 0) {
                synchronized (MainFabrica.lock) {
                    MainFabrica.lock.notify();
                }
                System.out.println("Hemos generado productos,"+
                        " En total tenemos: " + MainFabrica.productosGenerados);
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

