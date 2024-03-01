{% for include in includes %}
#include {{ include }}
{% endfor %}

using std::placeholders::_1;

class {{ class_name }} : public rclcpp::Node {
    public:
        {{ class_name }}() : Node({{ name }}), num {0, 0}, ready {false, false} {
            {% for subscriber in subscribers %}
            {{ subscriber.name }} = this->create_subscription<std_msgs::msg::{{ type }}>({{ subscriber.topic }}, 10, std::bind(&MinimalSubscriber::{{ subscriber.callback }}, this, _1));
            {% endfor %}
            {% for publisher in publishers %}
            {{ publisher.name }} = this->create_publisher<std_msgs::msg::{{ type }}>({{ publisher.topic }}, 10);
            {% endfor %}
        }
    private:
        void send() {
            {% for name in autos %}
            auto {{ name }} = std_msgs::msg::{{ type }}();
            {% endfor %}

            {{ autos[0] }}.data = num[0] + num[1];
            {{ autos[1] }}.data = num[0] - num[1];

            RCLCPP_INFO(this->get_logger(), "'%d' + '%d' = '%d'", num[0], num[1], {{ autos[0] }}.data);
            RCLCPP_INFO(this->get_logger(), "'%d' - '%d' = '%d'\n", num[0], num[1], {{ autos[1] }}.data);

            {% for publisher in publishers %}
            {{ publisher.name }}->publish({{ autos[publisher.num] }});
            {% endfor %}
        }

        {% for subscriber in subscribers %}
        void {{ subscriber.callback }}(const std_msgs::msg::{{ type }} & msg) {
            num[{{ subscriber.num }}] = msg.data;
            ready[{{ subscriber.num }}] = true;

            if (ready[0] && ready[1]) {
                ready[1] = ready[0] = false;
                send();
            }
        }
        {% endfor %}
        {% for subscriber in subscribers %}
        rclcpp::Subscription<std_msgs::msg::{{ type }}>::SharedPtr {{ subscriber.name }};
        {% endfor %}
        {% for publisher in publishers %}
        rclcpp::Publisher<std_msgs::msg::{{ type }}>::SharedPtr {{ publisher.name }};
        {% endfor %}
        int num[2];
        bool ready[2];
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalSubscriber>());
    rclcpp::shutdown();
    return 0;
}
