#include <stdio.h>
#include <stdlib.h>
#include "Filtro.hpp"
#include <iostream>

int main (int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Número de argumentos no válido\n");
		return 1;
	}
	
	int nvalor = atoi(argv[1]);
	std::ifstream ptr1(argv[2]);
	std::ifstream ptr2(argv[2]);
	if(!ptr1.is_open() || !ptr2.is_open()){
        std::cerr << "Error accediendo al archivo." << std::endl;
        return 1;
    }
	
	Mediamovil mediamovil = Mediamovil(nvalor);

	mediamovil.estadistico(&ptr1);

	Maximo maximo = Maximo();

	maximo.estadistico(&ptr2);
	
	return 0;
}