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

void imprimirPila(Pila *pila) {
	Nodo *nodo;
	int i = 0, j = 0, tipo = 0, valor = 0;
	char tipoC[1];
	nodo = pila -> cima;
	while(i < 4 || nodo != NULL) {
		for(j = 0; j < 13; j++) {
			tipo = (nodo -> elemento) % 10;
			valor = (nodo -> elemento) / 10;
			switch(tipo) {
				case 1:
					tipoC[0] = 'P';
					break;
				case 2:
					tipoC[0] = 'D';
					break;
				case 3:
					tipoC[0] = 'T';
					break;
				case 4:
					tipoC[0] = 'C';
					break;	
			}
			switch(valor){
				case 1:
					printf("[ A%c ] ", tipoC[0]);
					break;
				case 11:
					printf("[ J%c ] ", tipoC[0]);
					break;

				case 12:
					printf("[ Q%c ] ", tipoC[0]);
					break;

				case 13:
					printf("[ K%c ] ", tipoC[0]);
					break;	

				default: 
					printf("[ %i%c ] ", valor, tipoC[0]);
					break;	
			}
			nodo = nodo -> siguiente;
		}
		i++;
		printf("\n");
	}
}

void imprimirCartas() {
	int i = 0, j = 0;
	char tipo[1];
	for(i = 0; i < 4; i++) {
		for(j = 2; j <= 14; j++) {
			switch(i) {
				case 0:
					tipo[0] = 'P';
					break;
				case 1:
					tipo[0] = 'D';
					break;
				case 2:
					tipo[0] = 'T';
					break;
				case 3:
					tipo[0] = 'C';
					break;
			}
			switch(j) {
				case 11:
					printf("[ J%c ] ", tipo[0]);
				break;
				case 12:
					printf("[ Q%c ] ", tipo[0]);
				break;
				case 13:
					printf("[ K%c ] ", tipo[0]);
				break;
				case 14:
					printf("[ A%c ] ", tipo[0]);
				break;
				default:
					printf("[ %i%c ] ", j, tipo[0]);
			}
		}
		printf("\n");
	}
}

int main() {
	int carta = 0, i = 0, j = 0, numeroCarta = 0, valorDesapilado = 0,
 	tipoCarta = 0, contCartas = 0, arreglo[4][3], jugador[4], 
	numjug = 0, mayor = 0, cartasTipo = 0, contOnce = 0, sum = 0, v1 = 0; 
	char arregloTipos[4][3];
	
	imprimirCartas();
	
	printf("\n");
 	
	Pila pila;
	
	inicializarPila(&pila);
	
	srand(time(NULL));
	
	while(contCartas < 52) {
		numeroCarta = 1 + rand() % 13;
		tipoCarta = 1 + rand() % 4;
		carta = (numeroCarta * 10) + tipoCarta;
		if(estaRepetida(&pila, carta) != 1) {
			apilar(&pila, carta);
			contCartas++;
		}
	}
	printf("\n");
	imprimirPila(&pila);
	printf("\n");
	int cont = 0;
	while(cont < 3) { //Conversión a valor real de la carta
		for(i = 0; i < 4; i++) {
			valorDesapilado = desapilar(&pila);
			cartasTipo = valorDesapilado % 10;
			switch(cartasTipo) {
				case 1:
					arregloTipos[i][cont] = 'P';
					break;
				case 2:
					arregloTipos[i][cont] = 'D';
					break;
				case 3:
					arregloTipos[i][cont] = 'T';
					break;
				case 4:
					arregloTipos[i][cont] = 'C';
					break;
			}
			if(valorDesapilado < 20) {
				arreglo[i][cont] = 11;
			}else if(valorDesapilado > 99) {
				arreglo[i][cont] = 10;
			}else {
				valorDesapilado = valorDesapilado / 10;
				arreglo[i][cont] = valorDesapilado;
			}
		}
		cont++;
	}
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 3; j++) {
			printf("[ %i %c ]\n", arreglo[i][j], arregloTipos[i][j]);
		}
		printf("\n");
	}
	for(i = 0; i < 4; i++) { // Módulo para ganador y conteo de puntos
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
	if(mayor > 0) { // Módulo que muestra ganadores y perdedores
		for(i = 0; i < 4; i++) {
			if(i == numjug || mayor == jugador[i]) {
				printf("\nEl jugador %i", i+1);
				printf("\nGana con %i\n", mayor);
			}else {
				printf("\nEl jugador %i perdi%c\n", i+1, 162);
			}
		}
	}else {
		printf("\nNadie gana y todos pierden");
	}
	return 0;
}
