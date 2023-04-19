#!/usr/bin/env python3

import os
import sys
import random
import threading
import time


PARAMETROS_CORRECTOS = 2
RANGO_MINIMO = 5
RANGO_MAXIMO = 20
VALOR_ALEATORIO_MAXIMO = 32
VALOR_ALEATORIO_MINIMO = -32
HILOS = []

class MatricesHilos:
	matrizA = [];
	matrizB = [];
	matrizCS = [];
	matrizCH = [];
	
matricesHilos = MatricesHilos();

def main():

	if cantidadCorrectaDeParametros(len(sys.argv)) == False:
		print("No ingreso la cantidad correcta de parametros. Solo debe ingresar el valor de N");
		os._exit(1);
	
	parametro = sys.argv[1];
	
	if parametro.isnumeric() == False:
		print("Formato de parametro incorrecto. El parametro ingresado debe ser un numero.");
		os._exit(1);
		
	tamanio = int(parametro);
	
	if rangoValidoDeN(tamanio,RANGO_MINIMO,RANGO_MAXIMO) == False:
		print("El rango de N debe estar entre 5 y 20");
		os._exit(1);

	llenarEstructura(tamanio);
	llenarMatricesAleatorio();
	multiplicarMatricesSecuencial();
	multiplicarMatricesConHilos();
	for hilo in HILOS:
		hilo.join();
	mostrarMatrices();
	compararMatricesResultado();
	os._exit(0);
	
def cantidadCorrectaDeParametros(parametrosRecibidos):
	return parametrosRecibidos == PARAMETROS_CORRECTOS;
  
def rangoValidoDeN(valor, valorMinimo, valorMaximo):
	return valor >= valorMinimo and valor <= valorMaximo;

def llenarEstructura(tamanio):
	matricesHilos.matrizA = crearMatriz(tamanio);
	matricesHilos.matrizB = crearMatriz(tamanio);
	matricesHilos.matrizCS = crearMatriz(tamanio);
	matricesHilos.matrizCH = crearMatriz(tamanio);
	matricesHilos.tamanioDeMatriz = tamanio;
	return matricesHilos;

def crearMatriz(tamanioMatriz):
	matriz = [];
	for i in range(tamanioMatriz):
		matriz.append([]);
		for j in range(tamanioMatriz):
			matriz[i].append(0);
	return matriz;
 
def llenarMatricesAleatorio():
	for i in range(matricesHilos.tamanioDeMatriz):
		for j in range(matricesHilos.tamanioDeMatriz):
			matricesHilos.matrizA[i][j] = random.randrange(VALOR_ALEATORIO_MINIMO, VALOR_ALEATORIO_MAXIMO + 1);
			matricesHilos.matrizB[i][j] = random.randrange(VALOR_ALEATORIO_MINIMO, VALOR_ALEATORIO_MAXIMO + 1);


def multiplicarMatricesSecuencial():
	for i in range(matricesHilos.tamanioDeMatriz):
		for j in range(matricesHilos.tamanioDeMatriz):
			matricesHilos.matrizCS[i][j] = 0;
			for k in range(matricesHilos.tamanioDeMatriz):
				matricesHilos.matrizCS[i][j] += matricesHilos.matrizA[i][k] * matricesHilos.matrizB[k][j];

def multiplicarMatricesConHilos():
	
	for i in range(matricesHilos.tamanioDeMatriz):
		thread = threading.Thread(target=funcionEjecutadaPorHilo, args=(matricesHilos, i));
		thread.start();
		HILOS.append(thread);
			
def funcionEjecutadaPorHilo(matricesHilos, numeroHilo):
	for j in range(matricesHilos.tamanioDeMatriz):
		for k in range(matricesHilos.tamanioDeMatriz):
			matricesHilos.matrizCH[numeroHilo][j] += matricesHilos.matrizA[numeroHilo][k] * matricesHilos.matrizB[k][j];
	
def mostrarMatrices():
	mostrarMatriz(matricesHilos.matrizA, "Matriz A");
	mostrarMatriz(matricesHilos.matrizB, "Matriz B");
	mostrarMatriz(matricesHilos.matrizCS,"Matriz CS");
	mostrarMatriz(matricesHilos.matrizCH,"Matriz CH");
	
def mostrarMatriz(matriz, nombre):
	print(nombre);
	for i in range(matricesHilos.tamanioDeMatriz): 
		for j in range(matricesHilos.tamanioDeMatriz): 
			print("\t", matriz[i][j], end=" ");
		print();

def compararMatricesResultado():
	sonIguales = True;
	for i in range(matricesHilos.tamanioDeMatriz):
		for j in range(matricesHilos.tamanioDeMatriz):
      			if (matricesHilos.matrizCS[i][j] != matricesHilos.matrizCH[i][j]):
      				sonIguales = False;
      				break;
	if sonIguales:
		print("El producto matricial da lo mismo");
	else:
		print("El producto matricial da distinto");

main()