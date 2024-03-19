
#include <chrono>
#include <functional>
#include <pluginlib/class_loader.hpp>
#include <polygon_base/regular_polygon.hpp>
#include <rclcpp/rclcpp.hpp>
#include <string>

using namespace std::chrono_literals;

class plugin : public rclcpp::Node
{
public:
  plugin() : Node("plugin"), poly_loader("polygon_base", "polygon_base::RegularPolygon")
  {
    this->declare_parameter("polygon_base", "square::square");

    this->declare_parameter("side_length", 10.0);

    timer_ = this->create_wall_timer(1000ms, std::bind(&plugin::callback, this));
  }
  void callback()
  {
    std::string var_1 = this->get_parameter("polygon_base").as_string();

    double var_2 = this->get_parameter("side_length").as_double();

    try {
      std::shared_ptr<polygon_base::RegularPolygon> poligon =
        poly_loader.createSharedInstance(var_1);
      poligon->initialize(var_2);

      RCLCPP_INFO(this->get_logger(), "Polygon_base: %s", var_1.c_str());
      RCLCPP_INFO(this->get_logger(), "Side_length: %.2f", var_2);
      RCLCPP_INFO(this->get_logger(), "Area: %.2f\n", poligon->area());
    } catch (pluginlib::PluginlibException & ex) {
      printf("The plugin failed to load for some reason. Error: %s\n", ex.what());
    }
  }

private:
  pluginlib::ClassLoader<polygon_base::RegularPolygon> poly_loader;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<plugin>());
  rclcpp::shutdown();
  return 0;
}