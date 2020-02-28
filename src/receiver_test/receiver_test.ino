#include <VirtualWire.h>

void setup() {
  // default receive pin is 11
  vw_set_rx_pin(11);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  vw_rx_start();
  Serial.begin(9600);
}

void loop() {
  bool received = vw_wait_rx_max(5000);
  char buf[256];
  if (!received) {
    Serial.print("No message received.\n");
    return;
  }
  uint8_t bytes = sizeof(buf) - 1; // exclude last byte for null terminator
  bool verified = vw_get_message((uint8_t *) buf, &bytes);
  if (!verified) {
    Serial.print("Message corrupted.\n");
    return;
  }
  buf[bytes] = '\0';
  Serial.print("Received: ");
  Serial.print(buf);
  Serial.print('\n');
}
