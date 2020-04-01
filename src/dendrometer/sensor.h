#ifndef DENDROMETER_SENSOR_H
#define DENDROMETER_SENSOR_H
float read_sensor_voltage(void);
float voltage_to_distance(float);
bool sensor_calibrate_wanted(void);
#endif