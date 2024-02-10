#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void desapilar(Pila *pila) {
	Nodo *f;
	f = pila -> cima;
	pila -> cima = f -> siguiente;
	free(f);
}

void imprimirPila(Pila *pila) {
	Nodo *nodo;
	int i = 0;
	nodo = pila -> cima;
	for(i = 0; i < 12; i++) {
		printf("%i \n", nodo -> elemento);
		nodo = nodo -> siguiente;
	}
}

int main() {
	int numero = 0, i = 0, numeroCarta = 0;
	Pila pila;
	
	inicializarPila(&pila);
	
	srand(time(NULL));
	
	for(i = 0; i < 12; i++) {
		numero = 1 + rand() % 52;
		apilar(&pila, numero);
		//printf("Numero: %i\n", numero);
	}
	imprimirPila(&pila);
	printf("\n\n%i", longitudPila(&pila));
	return 0;
}
