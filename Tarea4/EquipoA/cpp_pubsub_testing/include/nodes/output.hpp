#ifndef __OUTPUT__HPP
#define __OUTPUT__HPP
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include <vector>

using std::placeholders::_1;

class MinimalOutput : public rclcpp::Node {
	public:
		MinimalOutput(std::vector<double> *buffer);
	private:
		void topic_callback(const std_msgs::msg::Float64 & msg);
		rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
		std::vector<double> *results;
};

#endif