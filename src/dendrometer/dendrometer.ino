#include "config.h"
#include "sensor.h"
#include "transmitter.h"
#include <Arduino.h>
#if DENDROMETER_TRANSMITTER == rf_transmitter
#include <VirtualWire.h>
#endif

float calibration_voltage = -1;

/* Core logic */
void calibrate(void) { calibration_voltage = read_sensor_voltage(); }

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
  Serial.begin(9600);
#if DENDROMETER_TRANSMITTER == rf_transmitter
  // default transmit pin is 12, but we are explicit about it
  vw_set_tx_pin(12);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  pinMode(LED_BUILTIN, OUTPUT);
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
