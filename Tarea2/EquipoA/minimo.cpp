#include "Filtro.hpp"

Minimo::Minimo () {
	first = true;
	minCurrent = 0;
}

double Minimo::filter (double number) {
	minCurrent = (first || number < minCurrent) ? number : minCurrent;
	first = false;
	return minCurrent;
}
