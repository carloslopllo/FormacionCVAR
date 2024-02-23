#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include <fstream>
#include "reader.hpp"
#include "nodes/publisher.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

MinimalPublisher::MinimalPublisher(std::vector<double> &read_vector)
    : Node("minimal_publisher"), count_(0)
{
  my_vector = std::move(read_vector);
  publisher_ = this->create_publisher<std_msgs::msg::Float64>("movingAverage", 10);
  timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
}

void MinimalPublisher::timer_callback()
{
  auto message = std_msgs::msg::Float64();
  if (!my_vector.empty())
  {
    message.data = my_vector.front();
    my_vector.erase(my_vector.begin());

    RCLCPP_INFO(this->get_logger(), "Publishing: '%lf'", message.data);

    publisher_->publish(message);
  }
}