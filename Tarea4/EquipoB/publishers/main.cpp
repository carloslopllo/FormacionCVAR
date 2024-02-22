#include <memory>
#include <deque>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
	public:
		MinimalSubscriber() : Node("main") {
			subscription_data_1 = this->create_subscription<std_msgs::msg::Int32>("data1", 10, std::bind(&MinimalSubscriber::callback_1, this, _1));
			subscription_data_2 = this->create_subscription<std_msgs::msg::Int32>("data2", 10, std::bind(&MinimalSubscriber::callback_2, this, _1));
			publisher_1 = this->create_publisher<std_msgs::msg::Int32>("sum", 10);
			publisher_2 = this->create_publisher<std_msgs::msg::Int32>("minus", 10);
		}
	private:
		void send() {
			auto sum = std_msgs::msg::Int32();
			auto minus = std_msgs::msg::Int32();

			int n1 = data1_dq.front();
			int n2 = data2_dq.front();

			sum.data = n1 + n2;
			minus.data = n1 - n2;

			data1_dq.pop_front();
			data2_dq.pop_front();

			RCLCPP_INFO(this->get_logger(), "'%d' + '%d' = '%d'", n1, n2, sum.data);
			RCLCPP_INFO(this->get_logger(), "'%d' - '%d' = '%d'\n", n1, n2, minus.data);

			publisher_1->publish(sum);
			publisher_2->publish(minus);
		}

		void callback_1(const std_msgs::msg::Int32 & msg) {
			data1_dq.push_back(msg.data);

			if (!data1_dq.empty() && !data2_dq.empty()) {
				send();
			}
		}
		void callback_2(const std_msgs::msg::Int32 & msg) {
			data2_dq.push_back(msg.data);

			if (!data1_dq.empty() && !data2_dq.empty()) {
				send();
			}
		}

		rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_data_1;
		rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_data_2;

		rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_1;
		rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_2;

		std::deque<int> data1_dq;
		std::deque<int> data2_dq;
};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MinimalSubscriber>());
	rclcpp::shutdown();
	return 0;
}
