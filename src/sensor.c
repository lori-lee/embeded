#include <intrins.h>
#include "STC15W408AS.h"
#include "sensor.h"
#include "interrupt.h"

void init_sensor (void)
{
    init_human_sensor ();
    init_light_sensor ();
}

static unsigned int read_ADC_result (int channel)
{
    prepare_ADC (channel);
    while (!is_ADC_over ()) _nop_ ();
    desctruct_ADC ();

    return get_ADC_result ();
}
