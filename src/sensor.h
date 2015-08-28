#if !defined __SENSOR_H__
#define __SENSOR_H__

#define init_human_sensor() 


extern void init_sensor (void);
extern unsigned int read_light_intensity_sensor (void);
#define read_human_sensor() P1_2
#endif
