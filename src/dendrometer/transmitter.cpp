#include "transmitter.h"
#include "config.h"
#include <Arduino.h>
#include <stdio.h>
#if DENDROMETER_TRANSMITTER == rf_transmitter
#include <VirtualWire.h>
#endif

void send_through_transmitter(float value) {
  Serial.print(value);
  Serial.print("\n");
#if DENDROMETER_TRANSMITTER == rf_transmitter
  char message[2048];
  // QUESTION: what if we want to send something more than 2047 bytes, however
  // unlikely that may be?
  sprintf(message, "%f", value);
  // light up
  digitalWrite(LED_BUILTIN, HIGH);
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();
  digitalWrite(LED_BUILTIN, LOW);
#endif
}