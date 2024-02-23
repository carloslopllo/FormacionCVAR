#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "statistics_lib/movingAverage.hpp"
#include "std_msgs/msg/float64.hpp"
#include "nodes/subscriber_member_function.hpp"

using std::placeholders::_1;

MinimalSubscriber::MinimalSubscriber(std::size_t tam_) : Node("minimal_subscriber"), m(tam_)
{
	this->declare_parameter("size", (int)tam_);
	
	subscription_ = this->create_subscription<std_msgs::msg::Float64>("movingAverage", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
	publisher_ = this->create_publisher<std_msgs::msg::Float64>("output", 10);
}
void MinimalSubscriber::topic_callback(const std_msgs::msg::Float64 &msg)
{
	int64_t size = this->get_parameter("size").as_int();
	m.resize(size);

	std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("size", size)};
	this->set_parameters(all_new_parameters);

	auto message = std_msgs::msg::Float64();
	message.data = m.statistical(msg.data);
	publisher_->publish(message);
}