#include "nodes/subscriber_member_function.hpp"

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MinimalSubscriber>(4));
	rclcpp::shutdown();
	return 0;
}