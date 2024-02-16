#ifndef __maximum_cpp__
#define __maximum_cpp__

#include "maximum.hpp"

maximum::maximum () {
	empty = true;
	maximumCurrent = 0;
}

double maximum::statistical (const double & number) {
	if (empty) {
		maximumCurrent = number;
		empty = false;
	} else if (maximumCurrent < number) {
		maximumCurrent = number;
	}

	return maximumCurrent;
}

#endif
