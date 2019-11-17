#include "config.h"
#include "transmitter.h"
#if DENDROMETER_TRANSMITTER == mock
#include "Arduino.h"
#endif

void send_through_transmitter(float value) {
  #if DENDROMETER_TRANSMITTER == mock
  Serial.print(value);
  Serial.print("\n");
  #endif
}