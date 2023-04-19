import java.util.Random;
public class Hilos {

    public static int[][] multiplicarMatircesHilos(int[][] matrizA, int[][] matrizB, int tamanio) throws InterruptedException
    {        
        int[][] resultado = new int[tamanio][tamanio];
        int numHilos = tamanio;
        Thread[] hilos = new Thread[numHilos];
        
        for (int i = 0; i < numHilos; i++)
        {
            hilos[i] = new Thread(new MultiplicacionHilos(matrizA, matrizB, resultado,i));
            hilos[i].start();
        }

        for (Thread hilo : hilos)
            hilo.join();

        return resultado;
    }

    private static class MultiplicacionHilos implements Runnable
    {
        private int[][] matrizA;
        private int[][] matrizB;
        private int[][] resultado;
        private int fila;

        public MultiplicacionHilos(int[][] a, int[][] b, int[][] resultado, int fila)
        {
            this.matrizA = a;
            this.matrizB = b;
            this.resultado = resultado;
            this.fila = fila;
        }

        @Override
        public void run() {
            int tamanio = matrizA.length;
            for (int i = 0; i < tamanio; i++)
            {
                int suma = 0;
                for(int j = 0; j < tamanio; j++)
                {
                    suma += matrizA[fila][j] * matrizB[j][i];
                }
                resultado[fila][i] = suma;
            }
        }
    }

    public static int[][] mutliplacarMatricesSecuencial(int[][] matrizA, int[][] matrizB)
    {
        int filasMatrizA = matrizA.length;
        int columnasMatrizA = matrizA[0].length;
        int filasMatrizB = matrizB.length;
        int columnasMatrizB = matrizB[0].length;

        if (columnasMatrizA != filasMatrizB)
        {
            throw new IllegalArgumentException("No se puede realizar la multiplicacion de matrices");
        }

        int[][] resultado = new int[filasMatrizA][columnasMatrizB];
        for(int i = 0; i < filasMatrizA; i++)
        {
            for(int j = 0; j < columnasMatrizB; j++)
            {
                for(int k = 0; k < columnasMatrizA; k++)
                {
                    resultado[i][j] += matrizA[i][k] * matrizB[k][j];
                }   
            }
        }
        return resultado;
    } 

    public static void cargarMatriz(int[][] matriz, int tamanio)
    {
        Random random = new Random();
        for (int i = 0; i < tamanio; i++)
        {
            for (int j = 0; j < tamanio; j++)
                matriz[i][j] = random.nextInt(65) - 32;
        }
    }

    public static void mostrarMatriz(int[][] matriz)
    {
        for (int i = 0; i < matriz.length; i++)
        {
            for (int j = 0; j < matriz.length; j++)
                System.out.print(matriz[i][j] + " ");
            System.out.println();
        }    
    }

    public static void inicializarMatriz(int[][] matriz)
    {
        for (int i = 0; i < matriz.length; i++)
        {
            for (int j = 0; j < matriz.length; j++)
            {
                matriz[i][j] = 0;
            }
        }
    }

    public static boolean sonMatricesIguales(int[][] matrizA, int[][] matrizB)
    {
        for (int i = 0; i < matrizA.length; i++)
        {
            for (int j = 0; j < matrizA.length; j++)
            {
                if (matrizA[i][j] != matrizB[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
	
  	public static boolean esNumero(String parametro)
	  {
		  try
		  {
			  int numero = Integer.parseInt(parametro);
			  return true;
		  }
		  catch( NumberFormatException ex)
		  {
			  System.out.println("El parametro no es un numero");
			  return false;
		  }
	  }
	
	public static boolean validarRango(int valor)
  {
		int rangoMinimo = 5;
	  int rangoMaximo = 20;
		if (valor <= rangoMinimo && valor >= rangoMaximo)
    {
      System.out.println("El tamaño de la matriz debe estar entre 5 y 20.");
      return false;
    }
		return true;
	}


    public static void mostrarResultado(int[][] matrizA, int[][] matrizB, int[][] matrizCS, int[][] matrizCH)
    {
        System.out.println("Matriz A: ");
        mostrarMatriz(matrizA);
        System.out.println("Matriz B: ");
        mostrarMatriz(matrizB);
        System.out.println("Matriz CS: ");
        mostrarMatriz(matrizCS);   
        System.out.println("Matriz CH: ");
        mostrarMatriz(matrizCH);   
    }

    public static void main(String[] args) throws Exception {
        if (args.length != 1)
        {   
            System.out.println("No se ha especificado ningun argumento que indique el tamaño de la matriz.");
            return;
        } 
        
        String parametro = args[0];

		    if (!esNumero(parametro))
		    {
          return;
        }	   
        
        int tamanio = Integer.parseInt(parametro);
        if (!validarRango(tamanio))
		    {
		    	return;
	  	  }		
		       
        int[][] matrizA = new int[tamanio][tamanio];
        int[][] matrizB = new int[tamanio][tamanio];
        
        cargarMatriz(matrizA, tamanio);
        cargarMatriz(matrizB, tamanio);
        
        int[][] matrizCS = new int[tamanio][tamanio];
        int[][] matrizCH = new int[tamanio][tamanio];
        inicializarMatriz(matrizCS);
        inicializarMatriz(matrizCH);

        matrizCS = mutliplacarMatricesSecuencial(matrizA, matrizB);

        try
        {
        matrizCH = multiplicarMatircesHilos(matrizA, matrizB, tamanio);
        } catch(InterruptedException e)
        {
            System.out.println("Error al multiplicar las matrices: " + e.getMessage());
            return;
        }  

        mostrarResultado(matrizA, matrizB, matrizCS, matrizCH);

        if (sonMatricesIguales(matrizCS, matrizCH))
        {
            System.out.println("La matrizCS es igual que la matrizCH");
        }
        else
        {
            System.out.println("La matrizCS no es igual que la matrizCH");
        }        
        return;
    }
}