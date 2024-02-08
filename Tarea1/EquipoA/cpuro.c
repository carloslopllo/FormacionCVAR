#include <stdio.h>
#include <stdlib.h>

int leer (FILE *f, float *l);
float mean (float *vector, float *suma, float leido, int tam, int index);

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

	float leido, sum = 0.0;
	float *v = (float *) malloc (nvalor * sizeof(float));
	if (v == NULL) {
		fprintf(stderr, "Error al reservar memoria dinámica\n");
		return 3;
	}

	for (int i = 0; i < nvalor; i++) {
		if (leer(f, &leido)) {
			v[i] = leido;
			sum = sum + leido;
		} else {
			fprintf(stderr, "No hay suficientes valores\n");
			return 4;
		}
	}

	printf("La media móvil es:\t%f\n", sum/nvalor);

	int j = 0;
	while (leer(f, &leido)) {
		printf("La media móvil es:\t%f\n", mean(v, &sum, leido, nvalor, j));
		j = (j + 1) % nvalor;
	}

	fclose(f);
	free(v);

	return 0;
}

int leer (FILE *f, float *l) {
	return (fscanf(f, "%f", l) == 1) ? 1 : 0;
}

float mean (float *vector, float *suma, float leido, int tam, int index) {
	float retirar = vector[index];
	*suma = *suma - retirar;
	vector[index] = leido;
	*suma = *suma + leido;
	return (*suma)/tam;
}
