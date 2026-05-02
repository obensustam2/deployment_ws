#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/battery_state.hpp"
#include <gtest/gtest.h>

TEST(BatteryMonitorIntegration, PublishesOnCorrectTopic){
    rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("test_subscriber");

    bool message_received = false;

    auto subscription = node->create_subscription<sensor_msgs::msg::BatteryState>(
        "battery_state",
        10,
        [&message_received](sensor_msgs::msg::BatteryState::SharedPtr msg){
            message_received = true;

            // verify message content
            EXPECT_GE(msg->percentage, 0.0f);
            EXPECT_LE(msg->percentage, 1.0f);
            EXPECT_TRUE(msg->present);
        }
    );

    // spin for 5 seconds waiting for a message
    std::chrono::seconds timeout = std::chrono::seconds(5);
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    while(!message_received && (std::chrono::steady_clock::now() - start < timeout)){
        rclcpp::spin_some(node);
    }

    EXPECT_TRUE(message_received) << "No message received on battery_state topic";

}


int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    rclcpp::shutdown();
    return result;
}


