cmake_minimum_required(VERSION 3.8)
project(deployment_pkg)


if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(battery_monitor src/battery_monitor.cpp)
ament_target_dependencies(battery_monitor rclcpp sensor_msgs)

install(TARGETS
  battery_monitor
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)

  # unit test
  ament_add_gtest(test_battery_monitor_unit test/test_battery_monitor_unit.cpp)
  ament_target_dependencies(test_battery_monitor_unit rclcpp sensor_msgs)

  # integration test
  ament_add_gtest(test_battery_monitor_integration test/test_battery_monitor_integration.cpp)
  ament_target_dependencies(test_battery_monitor_integration rclcpp sensor_msgs)
endif()

ament_package()
