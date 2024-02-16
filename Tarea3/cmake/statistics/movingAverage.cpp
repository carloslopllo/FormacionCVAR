#ifndef __movingAverage_cpp__
#define __movingAverage_cpp__

#include "movingAverage.hpp"

movingAverage::movingAverage (const std::size_t & size) {
	period = size;
	sum = 0;
}

double movingAverage::statistical (const double & number) {
	dq.push_back(number);

	if (period < dq.size()) {
		sum = sum - dq.front() + number;
		dq.pop_front();
	} else {
		sum = sum + number;
	}

	return sum/dq.size();
}

#endif
