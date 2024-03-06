{% for include in includes %}
#include {{ include }}
{% endfor %}

using std::placeholders::_1;

class {{ class_name }} : public rclcpp::Node {
	public:
		{{ class_name }}() : Node("{{ node_name }}") {
			{% for input in inputs %}
			sub_{{ input.topic }} = this->create_subscription<std_msgs::msg::{{ input.type }}>("{{ input.topic }}", 10, std::bind(&{{ class_name }}::callback_{{ input.topic }}, this, _1));
			{% endfor %}

			{% for output in outputs %}
			pub_{{ output.topic }} = this->create_publisher<std_msgs::msg::{{ output.type }}>("{{ output.topic }}", 10);
			{% endfor %}
		}

	private:
		{% for input in inputs %}
		void callback_{{ input.topic }} (const std_msgs::msg::{{ input.type }} & msg) {
			ins.input{{ loop.index }} = msg.data;
			trigger(ins, outs);

			{% for output in outputs %}
			auto {{ output.topic }} = std_msgs::msg::{{ output.type }}();
			{{ output.topic }}.data = outs.output{{ loop.index }};

			pub_{{ output.topic }}->publish({{ output.topic }});
			{% endfor %}
		}
		rclcpp::Subscription<std_msgs::msg::{{ input.type }}>::SharedPtr sub_{{ input.topic }};
		{% endfor %}

		{% for output in outputs %}
		rclcpp::Publisher<std_msgs::msg::{{ output.type }}>::SharedPtr pub_{{ output.topic }};
		{% endfor %}

		inputs ins;
		outputs outs;
};

int main(int argc, char **argv) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<MinimalSubscriber>());
	rclcpp::shutdown();
	return 0;
}
