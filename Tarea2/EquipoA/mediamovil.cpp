#include "Filtro.hpp"

Mediamovil::Mediamovil (size_t size) {
	nvalor = size;
	suma = 0;
}

double Mediamovil::filter (double number) {
	dq.push_back(number);
	if (dq.size() <= nvalor) {
		suma = suma + number;
	} else {
		suma = suma - dq.front() + number;
		dq.pop_front();
	}
	return suma/dq.size();
}
