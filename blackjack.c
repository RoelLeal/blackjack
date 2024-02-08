#include <stdio.h>
#include <math.h>

int main() {
	int numero = 0, i = 0;
	for(i = 0; i < 12; i++) {
		numero = 1 + rand() % 52;
		printf("Numero: %i\n", numero);
	}
	return 0;
}
