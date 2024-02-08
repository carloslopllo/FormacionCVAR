#include <stdio.h>
#include <stdlib.h>

#include <deque>


int leer (FILE *f, float *l);
float mean (std::deque<float> &dq, float *suma, float leido, int tam);

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
	std::deque<float> dq;
	
	for (int i = 0; i < nvalor; i++) {
		if (leer(f, &leido)) {
			dq.push_back(leido);
			sum = sum + leido;
		} else {
			fprintf(stderr, "No hay suficientes valores\n");
			return 3;
		}
	}
	
	printf("La media móvil es:\t%f\n", sum/nvalor);
	
	while (leer(f, &leido)) 
		printf("La media móvil es:\t%f\n", mean(dq, &sum, leido, nvalor));
	
	fclose(f);	
	return 0;
}

int leer (FILE *f, float *l) {
	return (fscanf(f, "%f", l) == 1) ? 1 : 0; 
}

float mean (std::deque<float> &dq, float *suma, float leido, int tam) {
	float retirar = dq.front();
	dq.pop_front();
    *suma = *suma - retirar;
	dq.push_back(leido);

	*suma = *suma + leido;
	return (*suma)/tam;
}