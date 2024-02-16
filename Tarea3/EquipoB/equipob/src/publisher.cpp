#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include <fstream>
#include "reader.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher(std::vector<double> read_vector)
    : Node("minimal_publisher"), count_(0)
    {
      my_vector = read_vector;
      publisher_ = this->create_publisher<std_msgs::msg::Float64>("topic", 10);
      timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

    

  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::Float64();
      if (!my_vector.empty()) {
        message.data = my_vector.front();
        my_vector.erase(my_vector.begin());

        RCLCPP_INFO(this->get_logger(), "Publishing: '%lf'", message.data);

        publisher_->publish(message);
      }
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
    size_t count_;
    std::vector<double> my_vector;

};

int main(int argc, char * argv[])
{
  
if(argc != 2)
  {
    std::cerr << "Error en el numero de argumentos" << std::endl;
    return 1;
  }

  //Abrimos el archivo
  std::ifstream ptr(argv[1]);

  std::vector<double> read_vector = readDouble(ptr);

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>(read_vector));
  rclcpp::shutdown();
  return 0;
}