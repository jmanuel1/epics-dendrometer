<!-- TODO: Call ourselves the Treehuggers. -->

# Tree Carbon Capture Dendrometer

This is the beginnings of an Arduino sketch for prototypes of a device that
measures the diameter of a tree. It is written to be able to support multiple
sensors and transmitting devices via compile-time configuration in
`src/dendrometer/config.h`.

## Test sketches

`receiver_test` and `transmitter_test` (in the `src/` folder) are Arduino
sketches to test the functionality of the [VirtualWire
library](http://www.airspayce.com/mikem/arduino/VirtualWire/). These sketches
are confirmed to work when pin 12 of one Arduino transmitting data is directly
connected to pin 11 of an Arduino receiving data, set up like in the following
schematic.

<!-- This schematic was drawn using CircuitLab. Unfortunately, you must pay to
save diagrams in CircuitLab, so this image is actually a screenshot. NOTE: I
suggest you find another service to draw schematics with. -->

![Two separate Arduinos. The ground pin of one Arduino connected to the ground
pin of the other. Pin 12 of the transmitting Arduino is connected, though a
wire, to pin 11 of the receiving Arduino.](docs/test_schematic.png)

### Loading the sketches onto Arduinos

Upload the `receiver_test` sketch to the Arduino that will receive data from the
other Arduino. Upload the `transmitter_test` sketch to the other Arduino.

### Running

When both Arduinos have power, the receiving Arduino should repeatedly output
the following through the serial port (i.e. USB if connected to a computer).

```
Received: hello there!
```

### Why are we using a superceded library?

It seems that there are many more easily found internet resources on VirtualWire
than there are on its replacement,
[RadioHead](http://www.airspayce.com/mikem/arduino/RadioHead/). Based on
RadioHead's list of supported chips, it's unclear whether it even supports the
hardware we're using!

