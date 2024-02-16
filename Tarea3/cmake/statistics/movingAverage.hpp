#ifndef __movingAverage_hpp__
#define __movingAverage_hpp__

#include "i_filter.hpp"
#include <deque>

class movingAverage : public i_filter {
	private:
		std::size_t period;
		double sum;
		std::deque<double> dq;
	public:
		movingAverage (const std::size_t & size);
		double statistical (const double & number) override;
};

#endif
