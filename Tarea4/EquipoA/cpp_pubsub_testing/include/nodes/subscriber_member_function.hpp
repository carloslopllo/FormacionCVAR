#ifndef __SUBSCRIBER_MEMBER__HPP
#define __SUBSCRIBER_MEMBER__HPP

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "statistics_lib/movingAverage.hpp"
#include "std_msgs/msg/float64.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
	public:
		MinimalSubscriber(std::size_t tam_);
	private:
		void topic_callback(const std_msgs::msg::Float64 & msg);
		rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
		rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
		movingAverage m;
};

#endif