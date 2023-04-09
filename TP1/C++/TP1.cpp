#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

#define HIJOS_DE_A 3
#define HIJOS_DE_B 2
#define HIJOS_DE_C 0
#define HIJOS_DE_D 1
#define HIJOS_DE_E HIJOS_DE_C
#define HIJOS_DE_F HIJOS_DE_E
#define HIJOS_DE_G HIJOS_DE_F

#define PROCESO_B 0
#define PROCESO_C 1
#define PROCESO_E 0

#define TIEMPO_DORMIDO 60
#define INICIO_ITERADOR 0
#define PROCESO_CREADO_CORRECTAMENTE 0
#define PROCESO_SIN_HIJOS 0
#define SALIDA_EXITOSA EXIT_SUCCESS
#define SALIDA_ERRONEA EXIT_FAILURE

bool procesoCreadoCorrectamente(pid_t pid);
void esperarPorMisHijos(int numeroHijos);
void mostrarMiInformacion(char letra, pid_t miPid, pid_t miParentPid);

bool procesoCreadoCorrectamente(pid_t pid)
{
  return pid >= PROCESO_CREADO_CORRECTAMENTE;
}

void esperarPorMisHijos(int numeroHijos)
{
  for (int i = INICIO_ITERADOR; i < numeroHijos; i++)
  {
    wait(NULL);
  }
}

void mostrarMiInformacion(char letra, pid_t miPid, pid_t miParentPid)
{
  std::cout<<"Soy el proceso "<<letra<<". Mi PID es "<<miPid<<" y el PID de mi padre es "<<miParentPid<<std::endl;
}

//Clase IProceso (simula una Interfaz)
class IProceso 
{
  protected:
    pid_t miPid;
    pid_t miPPid;
    char letra;
    int cantidadHijos;

  public:
    IProceso(pid_t pid, pid_t ppid, char caracter, int hijos) : miPid(pid), miPPid(ppid), letra(caracter), cantidadHijos(hijos) {}
    virtual void realizarAccion() = SALIDA_EXITOSA;
};

//Procesos que tienen hijos y deben esperarlos
class ProcesoConHijos : public IProceso 
{
  public:
    ProcesoConHijos(pid_t pid, pid_t ppid, char caracter, int hijos) : IProceso(pid, ppid, caracter, hijos) {}
    void realizarAccion() override 
    {
      mostrarMiInformacion(this->letra,this->miPid,this->miPPid);
      esperarPorMisHijos(this->cantidadHijos);
    }
};

//Procesos que no tienen hijos y deben hacer sleep
class ProcesoSinHijos : public IProceso 
{
  public:
    ProcesoSinHijos(pid_t pid, pid_t ppid, char caracter, int hijos) : IProceso(pid, ppid, caracter, hijos) {}
    void realizarAccion() override 
    {
      mostrarMiInformacion(this->letra,this->miPid,this->miPPid);
      sleep(TIEMPO_DORMIDO);
    }
};

class ProcesoFabrica
{
  public:
    IProceso* determinarTipoProceso(pid_t pid, pid_t ppid, char caracter, int hijos)
    {
      if (hijos > PROCESO_SIN_HIJOS)
      {
        proceso = new ProcesoConHijos(pid,ppid,caracter,hijos);
      }
      else
      {
        proceso = new ProcesoSinHijos(pid,ppid,caracter,hijos);
      }
      return proceso;
    }
  private:
    IProceso* proceso;
};

int main(int argc, char *argv[])
{
  pid_t pidProcesoA, pidProcesoB, pidProcesoD;
  ProcesoFabrica fabricaDeProcesos;

  for (int i = INICIO_ITERADOR; i < HIJOS_DE_A; i++)
  {
    pidProcesoA = fork();
    if (!procesoCreadoCorrectamente(pidProcesoA))
    {
      std::cout<<"Se ha producido un error al crear un nuevo proceso"<<std::endl;
      return SALIDA_ERRONEA;
    }
    if (!pidProcesoA)
    {
      if (i == PROCESO_B)
      {                
        for (int j = INICIO_ITERADOR; j < HIJOS_DE_B; j++)
        {
          pidProcesoB = fork();
          if (!procesoCreadoCorrectamente(pidProcesoB))
          {
            std::cout<<"Se ha producido un error al crear un nuevo proceso"<<std::endl;
            return SALIDA_ERRONEA;
          }
          if (!pidProcesoB)
          {
            if (j == PROCESO_E)
            {
              IProceso* procesoE = fabricaDeProcesos.determinarTipoProceso(getpid(),getppid(),'E',HIJOS_DE_E);
              procesoE->realizarAccion();
              return SALIDA_EXITOSA;
            }
            else
            {
              IProceso* procesoF = fabricaDeProcesos.determinarTipoProceso(getpid(),getppid(),'F',HIJOS_DE_F);
              procesoF->realizarAccion();
              return SALIDA_EXITOSA;
            }
          }                
        }
        IProceso* procesoB = fabricaDeProcesos.determinarTipoProceso(getpid(),getppid(),'B',HIJOS_DE_B);
        procesoB->realizarAccion();
        return SALIDA_EXITOSA;
      }
      else
      {
        if (i == PROCESO_C)
        {
          IProceso* procesoC = fabricaDeProcesos.determinarTipoProceso(getpid(),getppid(),'C',HIJOS_DE_C);
          procesoC->realizarAccion();
          return SALIDA_EXITOSA;
        }
        else
        {
          pidProcesoD = fork();
          if (!procesoCreadoCorrectamente(pidProcesoD))
          {
            std::cout<<"Se ha producido un error al crear un nuevo proceso"<<std::endl;
            return SALIDA_ERRONEA;
          }
          if (!pidProcesoD)
          {
            IProceso* procesoG = fabricaDeProcesos.determinarTipoProceso(getpid(),getppid(),'G',HIJOS_DE_G);
            procesoG->realizarAccion();
            return SALIDA_EXITOSA;
          }
          IProceso* procesoD = fabricaDeProcesos.determinarTipoProceso(getpid(),getppid(),'D',HIJOS_DE_D);
          procesoD->realizarAccion();
          return SALIDA_EXITOSA;
        }
      }    
    }
  }
  IProceso* procesoA = fabricaDeProcesos.determinarTipoProceso(getpid(),getppid(),'A',HIJOS_DE_A);
  procesoA->realizarAccion();
  return SALIDA_EXITOSA;
}