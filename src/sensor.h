#if !defined __SENSOR_H__
#define __SENSOR_H__

void init_sensor (void);
unsigned int read_light_intensity_sensor ();
bit read_human_sensor ();
#endif
