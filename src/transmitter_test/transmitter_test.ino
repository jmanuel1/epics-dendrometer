#include <VirtualWire.h>

void setup() {
  // default transmit pin is 12
  vw_set_tx_pin(12);  
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  const char *message = "hello there!"; // 12 chars
  // light up
  digitalWrite(LED_BUILTIN, HIGH);
  vw_send((uint8_t *) message, strlen(message));
  vw_wait_tx();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
