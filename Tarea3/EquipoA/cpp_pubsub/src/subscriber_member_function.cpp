#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "statistics_lib/movingAverage.hpp"
#include "std_msgs/msg/float64.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
	public:
		MinimalSubscriber() : Node("minimal_subscriber"), m(4) {
			this->declare_parameter("size", 4);

			subscription_ = this->create_subscription<std_msgs::msg::Float64>("movingAverage", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
			publisher_ = this->create_publisher<std_msgs::msg::Float64>("output", 10);
		}
	private:
		void topic_callback(const std_msgs::msg::Float64 & msg) {
			int64_t size = this->get_parameter("size").as_int();
			m.resize(size);

			std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("size", size)};
			this->set_parameters(all_new_parameters);

			auto message = std_msgs::msg::Float64();
			message.data = m.statistical(msg.data);
			publisher_->publish(message);
		}

		rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
		rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
		movingAverage m;
};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MinimalSubscriber>());
	rclcpp::shutdown();
	return 0;
}
