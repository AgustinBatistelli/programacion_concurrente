#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <ctype.h>
#include <cstring>

#define PARAMETROS_INCORRECTOS 0
#define N_FUERA_DE_RANGO PARAMETROS_INCORRECTOS
#define PARAMETRO_NO_ENTERO PARAMETROS_INCORRECTOS
#define ESPACIO_CARACTERES 6
#define INICIO_ITERADOR 0
#define PARAMETROS_CORRECTOS 2
#define RANGO_MINIMO 5
#define RANGO_MAXIMO 20
#define VALOR_ALEATORIO_MAXIMO 65
#define VALOR_ALEATORIO_NEGATIVO 32
#define EXITO 1
#define INICIALIZADOR 0

struct MatricesHilos
{
  int** matriz_a;
  int** matriz_b;
  int** matriz_cs;
  int** matriz_ch;
  int tamanio_matriz;
  int cantidad_hilos;
};

bool CantidadCorrectaDeParametros(int parametros_recibidos, int parametros_esperados);
bool ParametroNEsEntero(char* parametro);
bool RangoValidoN(int valor, int valor_minimo, int valor_maximo);
int** CrearMatriz(int tamanio_matriz);
void MostrarMatriz(int **matriz,int tamanio_matriz,const char* nombre);
MatricesHilos LlenarEstructura(int tamanio);
void LlenarMatricesAleatorio();
void MultiplicarMatricesSecuencial();
void MultiplicarMatricesConHilos(int cantidad_hilos);
void MostrarMatrices();
void FuncionEjecutadaPorHilo(int numero_hilo);
void CompararMatricesResultado();

MatricesHilos matriz_hilos;

int main(int argc, char* argv[])
{
  if(!CantidadCorrectaDeParametros(argc,PARAMETROS_CORRECTOS))
  {
    std::cout<<"No ingreso la cantidad correcta de parametros. Solamente debe ingresar un entero positivo"<<std::endl;
    return PARAMETROS_INCORRECTOS;
  }
  char* parametro_n = argv[1];
  if (!ParametroNEsEntero(parametro_n))
  {
    std::cout<<"El parametro que usted ingreso no es un entero positivo"<<std::endl;
    return PARAMETRO_NO_ENTERO;
  }
  int tamanio_matrices = atoi(argv[1]);
  if (!RangoValidoN(tamanio_matrices,RANGO_MINIMO,RANGO_MAXIMO))
  {
    std::cout<<"El rango de N debe estar entre 5 y 20"<<std::endl;
    return N_FUERA_DE_RANGO;
  }
  
  matriz_hilos = LlenarEstructura(tamanio_matrices);
  LlenarMatricesAleatorio();
  MultiplicarMatricesSecuencial();
  MultiplicarMatricesConHilos(matriz_hilos.cantidad_hilos);
  MostrarMatrices();
  CompararMatricesResultado();
  return EXITO;
}

bool CantidadCorrectaDeParametros(int parametros_recibidos, int parametros_esperados)
{
  return parametros_recibidos == parametros_esperados;
}

bool ParametroNEsEntero(char* parametro)
{
  for (int i = INICIO_ITERADOR; i < strlen(parametro); i++)
  {
    if (!isdigit(parametro[i]))
    {
      return false;
    }
  }
  return true;
}

bool RangoValidoN(int valor, int valor_minimo, int valor_maximo)
{
  return valor >= valor_minimo && valor <= valor_maximo;
}

int** CrearMatriz(int tamanio_matriz)
{
  int** matriz = new int*[tamanio_matriz];
  for (int i = INICIO_ITERADOR; i < tamanio_matriz; i++)
  {
    matriz[i] = new int[tamanio_matriz];
    for (int j = INICIO_ITERADOR; j < tamanio_matriz; j++)
    {
      matriz[i][j] = INICIALIZADOR;
    }
  }
  return matriz;
}

void MostrarMatriz(int **matriz,int tamanio_matriz,const char* nombre)
{
  std::cout<<nombre<<std::endl;
  for (int i = INICIO_ITERADOR; i < tamanio_matriz; i++)
  {
    for (int j = INICIO_ITERADOR; j < tamanio_matriz; j++)
    {
      std::cout << std::setw(ESPACIO_CARACTERES) << matriz[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

MatricesHilos LlenarEstructura(int tamanio)
{
  MatricesHilos matriz_hilo;
  matriz_hilo.matriz_a = CrearMatriz(tamanio);
  matriz_hilo.matriz_b = CrearMatriz(tamanio);
  matriz_hilo.matriz_cs = CrearMatriz(tamanio);
  matriz_hilo.matriz_ch = CrearMatriz(tamanio);    
  matriz_hilo.tamanio_matriz = matriz_hilo.cantidad_hilos = tamanio;
  return matriz_hilo;
}

void LlenarMatricesAleatorio()
{
  srand(time(NULL));
  for (int i = INICIO_ITERADOR; i < matriz_hilos.tamanio_matriz; i++)
  {
    for (int j = INICIO_ITERADOR; j < matriz_hilos.tamanio_matriz; j++)
    {
      matriz_hilos.matriz_a[i][j] = rand() % VALOR_ALEATORIO_MAXIMO - VALOR_ALEATORIO_NEGATIVO;
      matriz_hilos.matriz_b[i][j] = rand() % VALOR_ALEATORIO_MAXIMO - VALOR_ALEATORIO_NEGATIVO;
    }
  }    
}

void MultiplicarMatricesSecuencial()
{
  for (int i = INICIO_ITERADOR; i < matriz_hilos.tamanio_matriz; i++)
  {
    for (int j = INICIO_ITERADOR; j < matriz_hilos.tamanio_matriz; j++)
    {
      matriz_hilos.matriz_cs[i][j] = INICIALIZADOR;
      for (int k = INICIO_ITERADOR; k < matriz_hilos.tamanio_matriz; k++)
      {
        matriz_hilos.matriz_cs[i][j] += matriz_hilos.matriz_a[i][k] * matriz_hilos.matriz_b[k][j];
      }
    }
  }    
}

void MultiplicarMatricesConHilos(int cantidad_hilos)
{
  std::vector<std::thread> hilos;
  for (int i = INICIO_ITERADOR; i < cantidad_hilos; i++)
  {
    hilos.emplace_back(FuncionEjecutadaPorHilo,i);
  }
  for (auto& hilo : hilos) 
  {
    hilo.join();
  }
}

void MostrarMatrices()
{
  MostrarMatriz(matriz_hilos.matriz_a,matriz_hilos.tamanio_matriz,"Matriz A");
  MostrarMatriz(matriz_hilos.matriz_b,matriz_hilos.tamanio_matriz,"Matriz B");
  MostrarMatriz(matriz_hilos.matriz_cs,matriz_hilos.tamanio_matriz,"Matriz CS");
  MostrarMatriz(matriz_hilos.matriz_ch,matriz_hilos.tamanio_matriz,"Matriz CH");
}

void FuncionEjecutadaPorHilo(int numero_hilo)
{
  for (int j = INICIO_ITERADOR; j < matriz_hilos.tamanio_matriz; j++)
  {
    for (int k = INICIO_ITERADOR; k < matriz_hilos.tamanio_matriz; k++)
    {
      matriz_hilos.matriz_ch[numero_hilo][j] += matriz_hilos.matriz_a[numero_hilo][k] * matriz_hilos.matriz_b[k][j];
    }
  }
}

void CompararMatricesResultado()
{
  bool son_iguales = true;
  for (int i = INICIO_ITERADOR; i < matriz_hilos.tamanio_matriz; i++)
  {
    for (int j = INICIO_ITERADOR; j < matriz_hilos.tamanio_matriz; j++)
    {
      if (matriz_hilos.matriz_cs[i][j] != matriz_hilos.matriz_ch[i][j])
      {
        son_iguales = false;
        break;
      }
    }
  }
  if (son_iguales)
    std::cout<<"El producto matricial coincide"<<std::endl;
  else
    std::cout<<"El producto matricial no coincide"<<std::endl;
}