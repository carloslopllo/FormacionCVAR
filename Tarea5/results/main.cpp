
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber() : Node("main"), num{0, 0}, ready{false, false}
  {
    sub_1 = this->create_subscription<std_msgs::msg::Int32>(
      "data1", 10, std::bind(&MinimalSubscriber::callback_1, this, _1));

    sub_2 = this->create_subscription<std_msgs::msg::Int32>(
      "data2", 10, std::bind(&MinimalSubscriber::callback_2, this, _1));

    pub_1 = this->create_publisher<std_msgs::msg::Int32>("sum", 10);

    pub_2 = this->create_publisher<std_msgs::msg::Int32>("minus", 10);
  }

private:
  void send()
  {
    auto sum = std_msgs::msg::Int32();

    auto minus = std_msgs::msg::Int32();

    sum.data = num[0] + num[1];
    minus.data = num[0] - num[1];

    RCLCPP_INFO(this->get_logger(), "'%d' + '%d' = '%d'", num[0], num[1], sum.data);
    RCLCPP_INFO(this->get_logger(), "'%d' - '%d' = '%d'\n", num[0], num[1], minus.data);

    pub_1->publish(sum);

    pub_2->publish(minus);
  }

  void callback_1(const std_msgs::msg::Int32 & msg)
  {
    num[0] = msg.data;
    ready[0] = true;

    if (ready[0] && ready[1]) {
      ready[1] = ready[0] = false;
      send();
    }
  }

  void callback_2(const std_msgs::msg::Int32 & msg)
  {
    num[1] = msg.data;
    ready[1] = true;

    if (ready[0] && ready[1]) {
      ready[1] = ready[0] = false;
      send();
    }
  }

  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr sub_1;

  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr sub_2;

  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub_1;

  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub_2;

  int num[2];
  bool ready[2];
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
