#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node {
	public:
		MinimalPublisher() : Node("publisher_1"), data1(1) {
			publisher_ = this->create_publisher<std_msgs::msg::Int32>("data1", 10);

			timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
		}
	private:
		void timer_callback() {
			auto message = std_msgs::msg::Int32();
			message.data = data1;
			data1 = data1 + 2;

			RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.data);
			publisher_->publish(message);
		}

		rclcpp::TimerBase::SharedPtr timer_;
		rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
		int data1;
};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MinimalPublisher>());
	rclcpp::shutdown();
	return 0;
}
