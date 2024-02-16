#ifndef __read_hpp__
#define __read_hpp__

#include <fstream>

class read {
	public:
		read ();
		bool reading (std::ifstream & ptr, double & number);
};

#endif
