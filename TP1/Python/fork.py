import os
import time

hijos_del_proceso_a = ["B", "C", "D"]
hijos_del_proceso_b = ["E", "F"]
hijos_del_proceso_d = ["G"]

proceso_a = "A"
proceso_b = "B"
proceso_c = "C"
proceso_d = "D"

pid_hijos_del_proceso_a = []

def proceso_padre():
  mostrar_salida(proceso_a, os.getpid(), os.getppid()) 
  
  for hijo_de_a in hijos_del_proceso_a:
    pid = os.fork()
    
    if pid < 0 :
      print("Error al crear el nuevo procesos: ", hijo_de_a)
      os._exit(1)
    
    evaluar_pid(hijo_de_a, pid)

  proceso_pid_hijos(pid_hijos_del_proceso_a)
  os._exit(0)
    
def evaluar_pid(proceso_hijo, pid):
  if pid:
    pid_hijos_del_proceso_a.append(pid)  
  else:
    if proceso_hijo == proceso_b:
      procesos_hijos(proceso_b,hijos_del_proceso_b)
      os._exit(0)
    if proceso_hijo == proceso_c:
      mostrar_salida(proceso_c, os.getpid(), os.getppid())
      os._exit(0)
    else:
      procesos_hijos(proceso_d,hijos_del_proceso_d)
      os._exit(0) 

def procesos_hijos(proceso, lista_procesos_hijos):
  mostrar_salida(proceso, os.getpid(), os.getppid())
  pid_hijos_del_proceso = [] 
  for proceso_hijo in lista_procesos_hijos:
    pid = os.fork()
    if pid < 0 :
      print("Error al crear el nuevo procesos: ", proceso_hijo)
      os._exit(1)
    if pid:
         pid_hijos_del_proceso.append(pid)
    else:
        mostrar_salida(proceso_hijo, os.getpid(), os.getppid())
        os._exit(0)
  
  proceso_pid_hijos(pid_hijos_del_proceso)
  os._exit(0)  

def proceso_pid_hijos(pid_hijos_del_proceso):
  for pid_hijo in pid_hijos_del_proceso:
    os.waitpid(pid_hijo, 0)    

def mostrar_salida(nombre_proceso, pid, ppid):
  print("Proceso: ", nombre_proceso, " - PID: ", pid, " - PID del padre: ", ppid)
  time.sleep(10)

proceso_padre()