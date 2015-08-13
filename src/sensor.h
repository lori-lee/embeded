#if !defined __SENSOR_H__
#define __SENSOR_H__

extern void init_sensor (void);
extern unsigned int read_light_intensity_sensor (void);
extern bit read_human_sensor (void);
#endif
