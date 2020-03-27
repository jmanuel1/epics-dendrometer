/*
This code was written for a 13/16 in. diameter pvc pipe with a string wrapped
around it. This can measure a change in circumference of over 25 inches, which
translates to ~8.125 inches of diameter. Current length of the string is stored
even after the Arduino is reset/powered off.

Next steps: Take delta-diameter only from intermittent measurements Report
change in length wirelessly using IOT Determine power requirements for Arduino

Rotation sensor documentation:
https://wiki.dfrobot.com/Analog_Rotation_Sensor_V2__SKU__DFR0058_

1 bit = 3.6 degrees 100 bits = 360 degrees  1000 bits = 3600 degrees

There are 3.6 degrees to one bit read by the arduino, and 57.2958 degrees for
each radian. The equation for arc length is r*theta, where theta is measured in
radians. This equation and these conversion factors allow us to create a formula
for the amount of string pulled from our rotation prototype:
*/

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
double Distance = 0;


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  // sensor reads 1024 bits -> output is 0-3600 degrees
  outputValue = map(sensorValue, 0, 1023, 0, 3600);

  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // Distance in inches from rtheta, the equation for arclength
  Distance = outputValue*(13.0/16.0)*(1.0/2.0)*PI/180.0;

  // print the results to the serial monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t Degrees = ");
  Serial.print(outputValue);
  Serial.print("\t Inches = ");
  Serial.println(Distance);

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(20);
}



