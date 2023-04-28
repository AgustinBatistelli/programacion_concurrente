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

#define EXITO 1
#define FRACASO EXIT_FAILURE
#define NUMEROS_ENTEROS 4
#define NOMBRE_FIFO "./mififo"
#define ERROR_FIFO -1
#define INICIALIZADOR 0
#define PRIMERA_POSICION INICIALIZADOR

struct Numero
{
  int numeros[NUMEROS_ENTEROS];
  float promedio;
  int minimo;
  int maximo;
  int suma;
  int cantidad_numeros;
};

void OperarEstructura(Numero* numero);

int main(int argc, char* argv[])
{
  if (mkfifo(NOMBRE_FIFO, 0600) == ERROR_FIFO)
  {
    std::cout<<"Error al crear el fifo"<<std::endl;
    return FRACASO;
  }
  Numero numeros_para_cliente;
  int fifo_fd = open(NOMBRE_FIFO,O_RDONLY);
  if(read(fifo_fd,&numeros_para_cliente,sizeof(Numero)) == ERROR_FIFO)
  {
    std::cout<<"Error al leer del fifo"<<std::endl;
    return FRACASO;
  }
  close(fifo_fd);
  OperarEstructura(&numeros_para_cliente);
  fifo_fd = open(NOMBRE_FIFO,O_WRONLY);
  if(write(fifo_fd,&numeros_para_cliente,sizeof(Numero)) == ERROR_FIFO)
  { 
    std::cout<<"Error al escribir en el fifo"<<std::endl;
    return FRACASO;
  }
  close(fifo_fd);
  unlink(NOMBRE_FIFO);
  return EXITO;
}

void OperarEstructura(Numero* numero)
{
  for (int i = INICIALIZADOR; i < NUMEROS_ENTEROS; i++)
  {
    numero->suma+=numero->numeros[i];
    numero->cantidad_numeros++;
    if (i == PRIMERA_POSICION)
      numero->minimo = numero->maximo = numero->numeros[i];
    else
    {
      if(numero->numeros[i] < numero->minimo)
        numero->minimo = numero->numeros[i];
      if (numero->numeros[i] > numero->maximo)
        numero->maximo = numero->numeros[i];
    }
  }
  numero->promedio = (float)numero->suma/numero->cantidad_numeros;
}