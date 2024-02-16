#ifndef __minimum_hpp__
#define __minimum_hpp__

#include "i_filter.hpp"

class minimum : public i_filter {
	private:
		bool first;
		double minimumCurrent;
	public:
		minimum ();
		double statistical (const double & number) override;
};

#endif
