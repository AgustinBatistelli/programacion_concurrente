#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <ctype.h>
#include <cstring>
#include <regex>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define EXPRESION_REGULAR "^([1-9][0-9]*|0)-([1-9][0-9]*|0)-([1-9][0-9]*|0)-([1-9][0-9]*|0)$"
#define PARAMETROS_CORRECTOS 2
#define PARAMETROS_INCORRECTOS 0
#define ENTRADA_INCORRECTA PARAMETROS_INCORRECTOS
#define EXITO 1
#define NUMEROS_ENTEROS 4
#define SEPARADOR "-"
#define NOMBRE_FIFO "./mififo"
#define ERROR_FIFO -1
#define INICIALIZADOR 0
#define PRIMERA_POSICION INICIALIZADOR
#define FRACASO EXIT_FAILURE

struct Numero
{
  int numeros[NUMEROS_ENTEROS];
  float promedio;
  int minimo;
  int maximo;
  int suma;
  int cantidad_numeros;
};

bool CantidadCorrectaDeParametros(int parametros_recibidos, int parametros_esperados);
Numero LlenarEstructura(char* entrada);
void MostrarEstructura(Numero numero);

int main(int argc, char* argv[])
{
  if(!CantidadCorrectaDeParametros(argc,PARAMETROS_CORRECTOS))
  {
    std::cout<<"No ingreso la cantidad correcta de parametros. Debe ingresar 4 enteros separados por guion. Ej: 1-2-0-4"<<std::endl;
    return PARAMETROS_INCORRECTOS;
  }
  std::regex regex(EXPRESION_REGULAR);
  if (!std::regex_match(argv[1], regex))
  {
    std::cout<<"La entrada que ingreso NO es correcta"<<std::endl;
    return ENTRADA_INCORRECTA;
  }
  Numero numeros_operar = LlenarEstructura(argv[1]);
  int fifo_fd = open(NOMBRE_FIFO,O_WRONLY);
  if(write(fifo_fd,&numeros_operar,sizeof(Numero))==-1)
  {
    std::cout<<"Error al escribir en el fifo"<<std::endl;
    return FRACASO;
  }
  close(fifo_fd);

  fifo_fd = open(NOMBRE_FIFO,O_RDONLY);
  if(read(fifo_fd,&numeros_operar,sizeof(Numero)) == -1)
  {
    std::cout<<"Error al leer del fifo"<<std::endl;
    return FRACASO;
  }
  close(fifo_fd);
  MostrarEstructura(numeros_operar);
  return EXITO;
}

bool CantidadCorrectaDeParametros(int parametros_recibidos, int parametros_esperados)
{
  return parametros_recibidos == parametros_esperados;
}

Numero LlenarEstructura(char* entrada)
{
  Numero numero;
  numero.cantidad_numeros = numero.maximo = numero.minimo = numero.suma = 0;
  numero.promedio = INICIALIZADOR;
  int i = INICIALIZADOR;
  char* numero_obtenido = std::strtok(entrada, SEPARADOR);
  while (numero_obtenido != nullptr)
  {
    numero.numeros[i++] = std::stoi(numero_obtenido);
    numero_obtenido = std::strtok(nullptr, SEPARADOR);
  }
  return numero;
}

void MostrarEstructura(Numero numero)
{
  std::cout<<"Numeros pasados por parametro: ";
  for (int i = INICIALIZADOR; i < NUMEROS_ENTEROS; i++)
    std::cout<<numero.numeros[i]<<" ";
  std::cout << std::endl;
  std::cout<<"El promedio da: "<<numero.promedio<<std::endl;
  std::cout<<"El minimo es: "<<numero.minimo<<std::endl;
  std::cout<<"El maximo es: "<<numero.maximo<<std::endl;
  std::cout<<"La suma da: "<<numero.suma<<std::endl;
  std::cout<<"La cantidad de numeros es: "<<numero.cantidad_numeros<<std::endl;
}