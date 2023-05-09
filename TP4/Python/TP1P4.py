import os
import sys
import threading
import re

CANTIDAD_DE_HILOS = 2
ASCII_A_RESTAR = 64
UNO = 1
EXITO = 0
ERROR = UNO
PARAMETRO = UNO
DIVISOR_MITAD = 2
PARAMETROS_CORRECTOS = 2
RESTO_CERO = 0
INICIALIZADOR = RESTO_CERO
PRIMER_HILO = INICIALIZADOR
INICIALIZADOR_CADENA = ""
EXPRESION_REGULAR = "[^A-Za-z]"

lock = threading.Lock()

class DatosCadena:
	resto = INICIALIZADOR
	mitad = INICIALIZADOR
	cadena = INICIALIZADOR_CADENA
	resultado = []
	letra_convertida = INICIALIZADOR
	
datos_cadena = DatosCadena()

def main():

	if(not parametros_correctos()):
		print("Debe ingresar una palabra como parametro, sin numeros ni caracteres especiales")
		os._exit(ERROR)
	
	llenar_datos_cadena()
	crear_hilos()
	mostrar_resultado()
	os._exit(EXITO)
	
def parametros_correctos():
	return len(sys.argv) == PARAMETROS_CORRECTOS and not re.search(EXPRESION_REGULAR, sys.argv[PARAMETRO])
	
def llenar_datos_cadena():
	datos_cadena.cadena = sys.argv[PARAMETRO].upper()
	tamanio_de_palabra = len(datos_cadena.cadena)
	datos_cadena.resto = tamanio_de_palabra % DIVISOR_MITAD
	datos_cadena.mitad = int(tamanio_de_palabra / DIVISOR_MITAD)
	datos_cadena.resultado = [INICIALIZADOR for x in range(tamanio_de_palabra)]
	
def crear_hilos():
	hilos = []

	for i in range(CANTIDAD_DE_HILOS):
		thread = threading.Thread(target=generar_contrasenia, args=(obtener_cantidad_caracteres(i),));
		thread.start();
		hilos.append(thread);
		
	for hilo in hilos:
		hilo.join();
	
def generar_contrasenia(cantidad_de_caracteres):
	for _ in range(cantidad_de_caracteres):
		with lock:
			datos_cadena.resultado[datos_cadena.letra_convertida] = ord(datos_cadena.cadena[datos_cadena.letra_convertida]) - ASCII_A_RESTAR
			datos_cadena.letra_convertida += UNO
		
def obtener_cantidad_caracteres(hilo):
	if(datos_cadena.resto == RESTO_CERO or hilo == PRIMER_HILO):
		return datos_cadena.mitad
	return datos_cadena.mitad + UNO

def mostrar_resultado():
	print("Palabra ingresada: " + datos_cadena.cadena)		
	print("Contraseña generada: " + str(datos_cadena.resultado))

main()