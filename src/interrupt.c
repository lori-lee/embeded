#include "config.h"
#include "bulb.h"
#include "eprom.h"

extern sys_status g_sysstatus;
void update_sys_status ()
{
    //mark_status (l_sensor, read_light_intensity_sensor ());
    mark_status (h_sensor, read_human_sensor_sensor ());
    mark_status (e_relay, read_relay_status ());
}
void check_do (void)
{
    update_sys_status ();

    if (is_automode ()) {//auto mode
        if (human_detected ()) {//human detected ?
            mark_status (l_sensor, read_light_intensity_sensor ());
            if (is_dark ()) {//darkness ?
                turn_on_bulb ();
            } else {//
                //DO NOTHING
            }
        } else {//no human ?
            turn_off_bulb ();
        }
    } else {//manual mode ?
        if (need_save_config ()) {
            save_sys_config ();
            mark_status (manual_save_flag, 0);
        }
        if (is_relay_off () && !is_dark ()) {
            if (get_status (second_flag)) {
                inc_secs_elapsed ();
                mark_status (second_flag, 0);
                if (should_switch2auto ()) {//timeout in manual mode ?
                    switch2auto ();
                }
            }
        } else {
            mark_status (secs_elapsed, 0);
        }

    }
}
