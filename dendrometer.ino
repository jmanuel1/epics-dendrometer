#include <Arduino.h>
#include "src/dendrometer/config.h"
#include "src/dendrometer/sensor.h"
#include "src/dendrometer/transmitter.h"

float calibration_voltage = -1;

/* Core logic */
void calibrate(void) {
  calibration_voltage = read_sensor_voltage();
}

float calculate_distance() {
  float voltage = read_sensor_voltage();
  float distance = voltage_to_distance(voltage);
  return distance;
}

void send_to_receiver(float distance) {
  delay(1000); // delay for a second for manageable output
  send_through_transmitter(distance);
}

void setup() {
  #if DENDROMETER_TRANSMITTER == mock
  Serial.begin(9600);
  #endif
}

void loop() {
  if (sensor_calibrate_wanted()) {
    calibrate();
    return;
  }
  float distance = calculate_distance();
  send_to_receiver(distance);
}
