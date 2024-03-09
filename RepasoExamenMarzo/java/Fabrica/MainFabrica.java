package RepasoExamenMarzo.java.Fabrica;

public class MainFabrica {
    public static Object lock = new Object();
    public static int productosGenerados = 0;
    public static int productosGeneradosMaximo = 100;

    public static void main(String[] args) {
        Productores productores = new Productores();
        Consumidores consumidores = new Consumidores();
        Thread hiloProductores = new Thread(productores);
        Thread hiloConsumidores = new Thread(consumidores);
        hiloProductores.start();
        hiloConsumidores.start();
        

        try {
            hiloProductores.join();
            hiloConsumidores.join();
        } catch (InterruptedException e) {
        }
    }
}
