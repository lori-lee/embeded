#if !defined __SENSOR_H__
#define __SENSOR_H__
#include "STC15W408AS.h"

#define init_human_sensor() set_IO_mode (1, 2, 0x1)
#define read_human_sensor() (P1 & 0x80)
#define set_human_sensor_status(value)  (P1 |= 0x80) 

extern void init_sensor (void);
extern unsigned int read_light_intensity_sensor (void);
#endif
