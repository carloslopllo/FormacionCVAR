#ifndef __i_filter_hpp__
#define __i_filter_hpp__

namespace filter {
	class filter {
		public:
			virtual double statistical (const double &) = 0;
			virtual ~filter() {}
		protected:
			filter() {}
	};
}

#endif
