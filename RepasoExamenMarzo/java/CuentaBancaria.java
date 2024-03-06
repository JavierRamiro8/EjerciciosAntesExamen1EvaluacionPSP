package RepasoExamenMarzo.java;


  public class CuentaBancaria {
    private int saldo=500;    
    public synchronized void depositar(int cantidad) {
      saldo += cantidad;
    }
  
    public synchronized void retirar(int cantidad) {
      if (saldo >= cantidad) {
        saldo -= cantidad;
      }
    }
  
    public int getSaldo() {
      return saldo;
    }
  }