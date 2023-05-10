import java.util.concurrent.Semaphore;

public class Main {
    private int variableCompartida;
    private Semaphore semaforoProductor;
    private Semaphore semaforoConsumidor;
    final static int VALOR_ALEATORIO_MAXIMO = 100;
    final static int INICIALIZADOR = 0;
    final static int CICLOS_MAXIMOS = 10;
    final static int POSICION_SIGUIENTE = 1;

    public Main()
    {
        this.semaforoProductor = new Semaphore(1);
        this.semaforoConsumidor = new Semaphore(0);
    }

    public void ejecutarHilos()
    {
        Thread productor = new Thread(new Runnable() 
        {
            @Override
            public void run()
            {
                for(int i = INICIALIZADOR; i < CICLOS_MAXIMOS; i++)
                {
                    try 
                    {
                        semaforoProductor.acquire();
                        variableCompartida = (int) (Math.random() * VALOR_ALEATORIO_MAXIMO);
                        System.out.println("Iteracion "+(i+POSICION_SIGUIENTE)+". Soy el pruductor y acabo de producir: " + variableCompartida);
                        semaforoConsumidor.release();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        Thread consumidor = new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                for(int i = INICIALIZADOR; i < CICLOS_MAXIMOS; i++)
                {
                    try 
                    {
                        semaforoConsumidor.acquire();
                        int variableConsumida = variableCompartida;
                        System.out.println("Iteracion "+(i+POSICION_SIGUIENTE)+". Soy el consumidor y acabo de consumir: " + variableConsumida);
                        semaforoProductor.release();
                    } catch (Exception e) 
                    {
                        e.printStackTrace();
                    }
                }
            }
        }); 
        
        productor.start();
        consumidor.start();
    }

    public static void main(String[] args) {
        Main programa = new Main();
        programa.ejecutarHilos();
    }
}