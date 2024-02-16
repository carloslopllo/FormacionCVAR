#ifndef __minimum_cpp__
#define __minimum_cpp__

#include "minimum.hpp"

minimum::minimum () {
	first = true;
	minimumCurrent = 0;
}

double minimum::statistical (const double & number) {
	if (first) {
		minimumCurrent = number;
		first = false;
	} else if (number < minimumCurrent) {
		minimumCurrent = number;
	}

	return minimumCurrent;
}

#endif
