#include <stdio.h>
#include <stdlib.h>
#include "Filtro.hpp"

int leer (FILE *f, float *l);

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
	
	float leido, media;
	Mediamovil mediamovil = Mediamovil(nvalor);

	while (leer(f, &leido)) 
	    if (mediamovil.mean(leido, media))
            printf("La media móvil es:\t%f\n", media);
	
	fclose(f);	
	return 0;
}

int leer (FILE *f, float *l) {
	return (fscanf(f, "%f", l) == 1) ? 1 : 0; 
}