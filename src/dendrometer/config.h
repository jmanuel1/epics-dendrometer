#ifndef DENDROMETER_CONFIG_H
#define DENDROMETER_CONFIG_H

/* Rotation sensor (DFR0058) info */
#define ROTATION_SENSOR_RADIUS 3.1
#define ROTATION_SENSOR_CIRCUMFERENCE (2*PI*ROTATION_SENSOR_RADIUS)
#define ROTATION_SENSOR_VOLTS_PER_DEGREE 0.002/3

/* Config option values */
#define mock     0
// https://wiki.dfrobot.com/Analog_Rotation_Sensor_V2__SKU__DFR0058_
#define rotation 1

/* Config options */
#define DENDROMETER_SENSOR rotation
#define DENDROMETER_TRANSMITTER mock
#define DENROMETER_ROTATION_SENSOR_PIN A0
#endif
