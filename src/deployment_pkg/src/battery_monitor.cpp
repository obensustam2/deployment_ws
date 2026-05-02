#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/battery_state.hpp"

class BatteryMonitorNode : public rclcpp::Node{
private:
    rclcpp::Publisher<sensor_msgs::msg::BatteryState>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    float battery_level_;

    void publish_battery(){
        sensor_msgs::msg::BatteryState msg;
        msg.header.stamp = this->now();
        msg.percentage = battery_level_ / 100.0f;
        msg.voltage = 30.0f * msg.percentage;
        msg.present = true;
        RCLCPP_INFO_STREAM(this->get_logger(), "Battery voltage: " << msg.voltage);

        if (battery_level_ < 20.0f){
            RCLCPP_WARN_STREAM(this->get_logger(), "Low battery: " << battery_level_);
        }

        publisher_->publish(msg);
        battery_level_ -= 1.0f;
        
        if (battery_level_ < 0.0f){
            battery_level_ = 100.0f;
        }
    }

public:
    BatteryMonitorNode() : 
        Node("battery_monitor"), battery_level_(100.0f)
    {
        publisher_ = this->create_publisher<sensor_msgs::msg::BatteryState>("battery_state", 10);

        timer_ = this->create_wall_timer(
            std::chrono::seconds(1), 
            std::bind(&BatteryMonitorNode::publish_battery, this));

        RCLCPP_INFO(this->get_logger(), "Battery monitor started");
    }
};


int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BatteryMonitorNode>());
    rclcpp::shutdown();
    return 0;
}