#ifndef __maximum_hpp__
#define __maximum_hpp__

#include "i_filter.hpp"

class maximum : public i_filter {
	private:
		bool empty;
		double maximumCurrent;
	public:
		maximum ();
		double statistical (const double & number) override;
};

#endif
