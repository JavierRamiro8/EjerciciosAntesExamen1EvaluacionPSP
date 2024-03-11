package c.RepasoExamen;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ejercicio11 {

    public class ListarIPs {
        public static void main(String[] args) throws InterruptedException, IOException {
            String comando = "ipconfig";
            ProcessBuilder processBuilder = new ProcessBuilder(comando);

            Process proceso = processBuilder.start();
            BufferedReader reader = new BufferedReader(new InputStreamReader(proceso.getInputStream()));

            String linea;
            while ((linea = reader.readLine()) != null) {
                System.out.println(linea);
            }

            int exitCode = proceso.waitFor();
            System.out.println("Código de salida: " + exitCode);
        }
    }
}
