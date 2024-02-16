#include <iostream>
#include <memory>

#include "statistics.hpp"
#include "read.hpp"

int main (int argc, char **argv) {
	if (argc != 3) {
		std::cerr << argv[0] << " size file" << std::endl;
		return 1;
	}

	std::size_t size = std::stoi(argv[1]);
	std::ifstream ptr(argv[2]);
	if (!ptr.is_open()) {
		std::cerr << "Cannot open file" << std::endl;
		return 2;
	}

	double number;
	read r;

	std::shared_ptr<i_filter> filters[3] = {
		std::make_shared<movingAverage>(size),
		std::make_shared<maximum>(),
		std::make_shared<minimum>()
	};

	while (r.reading(ptr, number)) {
		std::cout << "Moving Average is:\t" << filters[0]->statistical(number) << std::endl;
		std::cout << "Maximum is:\t" << filters[1]->statistical(number) << std::endl;
		std::cout << "Minimum is:\t" << filters[2]->statistical(number) << std::endl;
		std::cout << std::endl;
	}

	return 0;
}
