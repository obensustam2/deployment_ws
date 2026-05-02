#pragma once

// Pure functions — easy to test
float calculate_percentage(float battery_level)
{
  return battery_level / 1.0f;
}

float calculate_voltage(float percentage)
{
  return 24.0f * percentage;
}

bool is_low_battery(float battery_level)
{
  return battery_level < 20.0f;
}
