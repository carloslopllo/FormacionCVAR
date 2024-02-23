#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include <vector>
#include "nodes/output.hpp"

using std::placeholders::_1;

MinimalOutput::MinimalOutput(std::vector<double> *buffer) : Node("output")
{
	subscription_ = this->create_subscription<std_msgs::msg::Float64>("output", 10, std::bind(&MinimalOutput::topic_callback, this, _1));
	results = buffer;
}
void MinimalOutput::topic_callback(const std_msgs::msg::Float64 &msg)
{
	RCLCPP_INFO(this->get_logger(), "movingAverage: '%f'", msg.data);
	results->push_back(msg.data);
}

rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
std::vector<double> *results;