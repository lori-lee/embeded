#if !defined __SENSOR_H__
#define __SENSOR_H__
#include "config.h"
#include "STC15W408AS.h"

#define init_human_sensor()     set_IO_mode (1, 2, 0x1)
#define init_light_sensor()     set_IO_mode (1, 0, 0x1)

extern void init_sensor (void);
static unsigned int read_ADC_result (int channel);

#define read_human_sensor()             read_ADC_result(2)
#define read_light_intensity_sensor()   read_ADC_result(0)
#endif
