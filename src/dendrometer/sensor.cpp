#include "config.h"
#include "sensor.h"
#include "Arduino.h"

extern float calibration_value, calibration_voltage;

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
  return voltage/1000.0;
  #endif
}

float distance_to_degrees(float distance) {
  return distance/ROTATION_SENSOR_CIRCUMFERENCE*360;
}

// find what voltage corresponds to zero based on calibration
float find_voltage_for_zero() {
  if (calibration_value < 0) {
    Serial.print("ERROR: Sensor needs to be calibrated!");
    return -1;
  }
  const float calibration_degrees = distance_to_degrees(calibration_value);
  const float voltage_for_zero = calibration_voltage -
    calibration_degrees*ROTATION_SENSOR_VOLTS_PER_DEGREE;
  return voltage_for_zero;
}

// returns inches
float voltage_to_distance(float voltage) {
  #if DENDROMETER_SENSOR == mock
  return voltage*8;
  #elif DENDROMETER_SENSOR == rotation
  const float voltage_for_zero = find_voltage_for_zero();
  float degrees;
  degrees = (voltage - voltage_for_zero)/ROTATION_SENSOR_VOLTS_PER_DEGREE;
  const float inches_per_mm = 1/25.4;
  return degrees/360*2*PI*ROTATION_SENSOR_RADIUS*inches_per_mm;
  #endif
}

bool sensor_calibrate_wanted(float *value) {
  #if DENDROMETER_SENSOR == mock
  static bool wanted = true;
  if (wanted) {
    wanted = false;
    *value = 2;
    return true;
  }
  return wanted;
  #elif DENDROMETER_SENSOR == rotation
  // calibrate to zero at sketch start
  static bool wanted = true;
  if (wanted) {
    wanted = false;
    *value = 0;
    return true;
  }
  return wanted;
  #endif
}