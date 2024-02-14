#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 1 - PICAS    2 - DIAMANTES
// 3 - TREBOL   4 - CORAZONES

typedef int Carta;

typedef struct nodo {
	Carta elemento;
	struct nodo *siguiente;
}Nodo;

typedef struct {
	Nodo *cima;
}Pila;

void inicializarPila(Pila *pila) {
	pila -> cima = NULL;
}

void apilar(Pila *pila, Carta elemento) {
	Nodo *nuevo;
	nuevo = (Nodo*) malloc(sizeof(Nodo));
	nuevo -> elemento = elemento;
	nuevo -> siguiente = pila -> cima;
	pila -> cima = nuevo;
}

int longitudPila(Pila *pila) {
	Nodo *nodo;
	int cont = 0;
	nodo = pila -> cima;
	while(nodo != NULL) {
		cont++;
		nodo = nodo -> siguiente;
	}
	return cont;
}

int desapilar(Pila *pila) {
	int elem = 0;
	Nodo *f;
	f = pila -> cima;
	pila -> cima = f -> siguiente;
	elem = f -> elemento;
	free(f);
	return elem;
}

void imprimirPila(Pila *pila) {
	Nodo *nodo;
	int i = 0;
	nodo = pila -> cima;
	while(nodo != NULL) {
		printf("%i \n", nodo -> elemento);
		nodo = nodo -> siguiente;
	}
}

int estaRepetida(Pila *pila, int carta) {
	Nodo *nodo;
	int bandera = 0;
	nodo = pila -> cima;
	while(nodo != NULL) {
		if(carta == nodo -> elemento) {
			bandera = 1;
			break;
		}
		nodo = nodo -> siguiente;
	}
	return bandera;
}

int main() {
	int carta = 0, i = 0, j = 0, numeroCarta = 0, valorDesapilado = 0,
 	tipoCarta = 0, contCartas = 0, arreglo[4][3], temp = 0, jugador[4], 
	numjug = 0, mayor = 0, contOnce = 0, sum = 0, v1 = 0;
 	
	Pila pila;
	
	inicializarPila(&pila);
	
	srand(time(NULL));
	
	while(contCartas < 12) {
		numeroCarta = 1 + rand() % 13;
		tipoCarta = 1 + rand() % 4;
		carta = (numeroCarta * 10) + tipoCarta;
		if(estaRepetida(&pila, carta) != 1) {
			apilar(&pila, carta);
			contCartas++;
		}
		//printf("Numero: %i\n", carta);
	}
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 3; j++) {
			valorDesapilado = desapilar(&pila);
			if(valorDesapilado < 20) {
				arreglo[i][j] = 11;
			}else if(valorDesapilado > 99) {
				arreglo[i][j] = 10;
			}else {
				valorDesapilado = valorDesapilado / 10;
				arreglo[i][j] = valorDesapilado;
			}
		}
	}
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 3; j++) {
			printf("%i\n", arreglo[i][j]);
		}
		printf("\n");
	}
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 3; j++) {
			if(arreglo[i][j] == 11)
				contOnce++;
			jugador[i] += arreglo[i][j];
		}
		while(contOnce > 0 && jugador[i] > 21) {
			jugador[i] -= 10;
			contOnce--;
		}
		contOnce = 0;
		if(jugador[i] > mayor && jugador[i] <= 21){
   			mayor = jugador[i];
   			numjug = i;
	   	}
	   	printf("[%i] Total: %i\n", i+1, jugador[i]);
	}
	
    printf("\nEl jugador %i",numjug+1);
	printf("\nGana con %i\n", mayor);
	
	for(i = 0; i < 4; i++) {
		if(i != numjug) {
			printf("\nEl jugador %i perdi%c", i+1, 162);
		}
	}

	return 0;
}
