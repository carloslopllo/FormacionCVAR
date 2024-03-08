
#include <memory>

#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/int32.hpp"

#include "central_node_pkg/trigger.hpp"


using std::placeholders::_1;

class node : public rclcpp::Node {
	public:
		node() : Node("node") {
			
			sub_data1 = this->create_subscription<std_msgs::msg::Int32>("data1", 10, std::bind(&node::callback_data1, this, _1));
			
			sub_data2 = this->create_subscription<std_msgs::msg::Int32>("data2", 10, std::bind(&node::callback_data2, this, _1));
			

			
			pub_sum = this->create_publisher<std_msgs::msg::Int32>("sum", 10);
			
			pub_minus = this->create_publisher<std_msgs::msg::Int32>("minus", 10);
			
		}

	private:
		
		void callback_data1 (const std_msgs::msg::Int32 & msg) {
			ins.input1 = msg.data;
			trigger(ins, outs);

			
			auto sum = std_msgs::msg::Int32();
			sum.data = outs.output1;

			pub_sum->publish(sum);
			
			auto minus = std_msgs::msg::Int32();
			minus.data = outs.output2;

			pub_minus->publish(minus);
			
		}
		rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr sub_data1;
		
		void callback_data2 (const std_msgs::msg::Int32 & msg) {
			ins.input2 = msg.data;
			trigger(ins, outs);

			
			auto sum = std_msgs::msg::Int32();
			sum.data = outs.output1;

			pub_sum->publish(sum);
			
			auto minus = std_msgs::msg::Int32();
			minus.data = outs.output2;

			pub_minus->publish(minus);
			
		}
		rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr sub_data2;
		

		
		rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub_sum;
		
		rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pub_minus;
		

		inputs ins;
		outputs outs;
};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<node>());
	rclcpp::shutdown();
	return 0;
}