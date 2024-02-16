#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
	public:
		MinimalSubscriber() : Node("output") {
			subscription_ = this->create_subscription<std_msgs::msg::Float64>("output", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
		}
	private:
		void topic_callback(const std_msgs::msg::Float64 & msg) {
			RCLCPP_INFO(this->get_logger(), "movingAverage: '%f'", msg.data);
		}

		rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MinimalSubscriber>());
	rclcpp::shutdown();
	return 0;
}
