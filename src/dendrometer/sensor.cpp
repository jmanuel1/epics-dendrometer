#include "sensor.h"
#include "config.h"
#include <Arduino.h>

extern float calibration_voltage;

// Map value to 0-5000mV
int map_value_to_5000(int sensor_value) {
  return map(sensor_value, 0, 1023, 0, 5000);
}

float read_sensor_voltage(void) {
#if DENDROMETER_SENSOR == mock
  return 0.5;
#elif DENDROMETER_SENSOR == rotation
  const int sensor_value = analogRead(DENROMETER_ROTATION_SENSOR_PIN);
  const int voltage = map_value_to_5000(sensor_value);
  return voltage / 1000.0;
#endif
}

float distance_to_degrees(float distance) {
  return distance / ROTATION_SENSOR_CIRCUMFERENCE * 360;
}

// find what voltage corresponds to zero based on calibration
float find_voltage_for_zero() { return calibration_voltage; }

// returns inches
float voltage_to_distance(float voltage) {
#if DENDROMETER_SENSOR == mock
  return voltage * 8;
#elif DENDROMETER_SENSOR == rotation
  // TODO: I should not make this relative to a 'zero' voltage because we want
  // to remember the rotation after the Arduino is powered off.
  const float voltage_for_zero = find_voltage_for_zero();
  float degrees;
  degrees = (voltage - voltage_for_zero) / ROTATION_SENSOR_VOLTS_PER_DEGREE;
  const float inches_per_mm = 1 / 25.4;
  return // Distance in inches from rtheta, the equation for arclength
      degrees * (13.0 / 16.0) * (1.0 / 2.0) * PI / 180.0;
#endif
}

bool sensor_calibrate_wanted(void) {
  // calibrate to zero at sketch start
  static bool wanted = true;
  wanted = false;
  if (wanted) {
    return true;
  }
  return wanted;
}