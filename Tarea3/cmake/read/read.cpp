#ifndef __read_cpp__
#define __read_cpp__

#include "read.hpp"

read::read () {

}

bool read::reading (std::ifstream & ptr, double & number) {
	return (ptr >> number) ? true : false;
}

#endif
