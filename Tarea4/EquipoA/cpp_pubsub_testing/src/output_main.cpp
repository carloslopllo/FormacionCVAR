#include "nodes/output.hpp"

int main(int argc, char **argv) {

	std::vector<double> vect;

	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MinimalOutput>(&vect));

	std::cout << vect[0] << std::endl;
	rclcpp::shutdown();
	return 0;
}