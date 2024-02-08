#include <stdio.h>
#include <stdlib.h>
#include "Filtro.hpp"

int leer (FILE *f, double *l);

int main (int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Número de argumentos no válido\n");
		return 1;
	}
	
	int nvalor = atoi(argv[1]);
	FILE *f = fopen(argv[2], "r");
	if (f == NULL) {
		fprintf(stderr, "Error al abrir el fichero\n");
		return 2;
	}
	
	double leido;
	Mediamovil mediamovil = Mediamovil(nvalor);
	Minimo minimo = Minimo();

	while (leer(f, &leido)) {
	    printf("La media móvil es:\t%f\n", mediamovil.filter(leido));
	    printf("El mínimo es:\t\t%f\n", minimo.filter(leido));
	}
	
	fclose(f);	
	return 0;
}

int leer (FILE *f, double *l) {
	return (fscanf(f, "%lf", l) == 1) ? 1 : 0; 
}
