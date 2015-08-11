#include "config.h"
#include "sensor.h"

extern sys_status data g_sysstatus;
void check_do (void)
{
    if (!get_status (mode)) {//auto mode
        if (get_status (h_sensor)) {//human detected ?
            if (get_status (l_sensor) <= get_config (light_threshold)) {//darkness ?
                turn_on_bulb ();
            } else {//
            }
        } else {//no human ?
            turn_off_bulb ();
        }
    } else {//manual mode
        if (get_status (secs_elapsed) <= 0) {//timeout in manual mode ?
            mark_status (mode, 1);//switch to auto mode
        }
    }
}
