#include <memory>
#include <deque>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node {
    public:
        MinimalSubscriber() : Node({{ name }}) {
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

            {% for n in rest %}
            int {{ n.name }} = {{ n.deque }}.front();
            {{ n.deque }}.pop_front();
            {% endfor %}

            {{ autos[0] }}.data = {{ rest[0]["name"] }} + {{ rest[1]["name"] }};
            {{ autos[1] }}.data = {{ rest[0]["name"] }} - {{ rest[1]["name"] }};

            RCLCPP_INFO(this->get_logger(), "'%d' + '%d' = '%d'", n1, n2, sum.data);
            RCLCPP_INFO(this->get_logger(), "'%d' - '%d' = '%d'\n", n1, n2, minus.data);

            {{ publishers[0]["name"] }}->publish({{ autos[0] }});
            {{ publishers[1]["name"] }}->publish({{ autos[1] }});
        }

        {% for subscriber in subscribers %}
        void {{ subscriber.callback }}(const std_msgs::msg::{{ type }} & msg) {
            {{ subscriber.deque }}.push_back(msg.data);

            if (!{{ deque[0] }}.empty() && !{{ deque[1] }}.empty()) {
                send();
            }
        }
        rclcpp::Subscription<std_msgs::msg::{{ type }}>::SharedPtr {{ subscriber.name }};
        {% endfor %}

        {% for publisher in publishers %}
        rclcpp::Publisher<std_msgs::msg::{{ type }}>::SharedPtr {{ publisher.name }};
        {% endfor %}

        {% for n in rest %}
        {{ n.type }} {{ n.deque }};
        {% endfor %}
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalSubscriber>());
    rclcpp::shutdown();
    return 0;
}
