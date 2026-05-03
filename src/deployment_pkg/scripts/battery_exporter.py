#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import BatteryState
from prometheus_client import start_http_server, Gauge

# Define Prometheus metrics
BATTERY_PERCENTAGE = Gauge(
    'robot_battery_percentage',
    'Battery percentage of the robot (0.0 to 1.0)'
)

BATTERY_VOLTAGE = Gauge(
    'robot_battery_voltage',
    'Battery voltage of the robot in volts'
)

BATTERY_PRESENT = Gauge(
    'robot_battery_present',
    'Whether the battery is present (1=yes, 0=no)'
)


class BatteryExporterNode(Node):
    def __init__(self):
        super().__init__('battery_exporter')

        # subscribe to battery state topic
        self.subscription = self.create_subscription(
            BatteryState,
            'battery_state',
            self.battery_callback,
            10
        )

        self.get_logger().info('Battery exporter started — metrics at :9090/metrics')

    def battery_callback(self, msg):
        # update Prometheus metrics when message arrives
        BATTERY_PERCENTAGE.set(msg.percentage)
        BATTERY_VOLTAGE.set(msg.voltage)
        BATTERY_PRESENT.set(1.0 if msg.present else 0.0)

        self.get_logger().info(
            f'Metrics updated — voltage: {msg.voltage:.2f}V  percentage: {msg.percentage:.2f}'
        )


def main():
    # start Prometheus HTTP server on port 9090
    start_http_server(9090)
    print('Prometheus metrics server started on port 9090')

    rclpy.init()
    node = BatteryExporterNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()