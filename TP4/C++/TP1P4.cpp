#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <ctype.h>
#include <cstring>
#include <random>
#include <mutex>

#define EXITO 1
#define VALOR_ALEATORIO_MAXIMO 100
#define TAMANIO_ARRAY 10
#define CANTIDAD_HILOS 2
#define MITAD 2
#define MITAD_DEL_ARRAY TAMANIO_ARRAY/MITAD
#define INICIALIZADOR 0
#define INICIO_ITERADOR INICIALIZADOR
#define UNO 1

struct RangoHilos
{
  int valor_inicial;
  int valor_final;
};

std::mutex mutex;
int suma_array = INICIALIZADOR;
int array[TAMANIO_ARRAY];

void LlenarArrayAleatoriamente();
void MostrarArray();
void MostrarSumaArray();
void SumarArray();
RangoHilos AsignarRangoHilos(int limite_inferior, int limite_superior);
void FuncionEjecutadaPorHilo(RangoHilos rango_hilo);

int main()
{
  LlenarArrayAleatoriamente();
  MostrarArray();
  SumarArray();
  MostrarSumaArray();
  return EXITO;
}

void LlenarArrayAleatoriamente()
{
  std::random_device dispositivo_azar;
  std::mt19937 generador_aleatorio(dispositivo_azar());
  std::uniform_int_distribution<> distribucion_aleatoria(INICIALIZADOR, VALOR_ALEATORIO_MAXIMO);
  for (int i = INICIO_ITERADOR; i < TAMANIO_ARRAY; i++)
    array[i] = distribucion_aleatoria(generador_aleatorio); 
}

void MostrarArray()
{
  std::cout <<"Valores del array: "<< std::endl;
  for (int i = INICIO_ITERADOR ; i < TAMANIO_ARRAY; i++)
    std::cout<<array[i]<<" ";
  std::cout << std::endl;
}

void MostrarSumaArray()
{
  std::cout <<"La suma de los valores del array da: "<<suma_array<< std::endl;
}

void SumarArray()
{
  std::vector<std::thread> hilos;
  for (int i = INICIALIZADOR; i < CANTIDAD_HILOS; i++)
    hilos.emplace_back(FuncionEjecutadaPorHilo,AsignarRangoHilos(i*MITAD_DEL_ARRAY,TAMANIO_ARRAY-(MITAD_DEL_ARRAY*(UNO-i))));
  for (auto& hilo : hilos) 
    hilo.join();
}

RangoHilos AsignarRangoHilos(int limite_inferior, int limite_superior)
{
  RangoHilos rango;
  rango.valor_inicial = limite_inferior;
  rango.valor_final = limite_superior;
  return rango;
}

void FuncionEjecutadaPorHilo(RangoHilos rango_hilo)
{
  for (int i = rango_hilo.valor_inicial; i < rango_hilo.valor_final; i++)
  {
    mutex.lock();
    suma_array += array[i];
    mutex.unlock();
  }
}