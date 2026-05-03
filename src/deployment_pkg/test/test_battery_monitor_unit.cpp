#include "rclcpp/rclcpp.hpp"
#include <gtest/gtest.h>
#include "deployment_pkg/battery_utils.hpp"

// Test 1: battery percentage stays in valid range [0.0, 1.0]
TEST(BatteryMonitorUnit, PercentageRange) {
  EXPECT_GE(calculate_percentage(74.5f), 0.0f);
  EXPECT_LE(calculate_percentage(74.5f), 1.0f);
}

TEST(BatteryMonitorUnit, VoltageScaling){
    EXPECT_FLOAT_EQ(calculate_voltage(0.5f), 15.0f);
}

TEST(BatteryMonitorUnit, LowBatteryThreshold){
    EXPECT_TRUE(is_low_battery(15.0f));
    EXPECT_FALSE(is_low_battery(100.0f));
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  testing::InitGoogleTest(&argc, argv);

  // run only this specific test
  // ::testing::GTEST_FLAG(filter) = "BatteryMonitorUnit.PercentageRange";

  int result = RUN_ALL_TESTS();
  rclcpp::shutdown();
  return result;
}
