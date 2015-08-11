#include "config.h"
#include "bulb.h"

extern sys_status g_sysstatus;
void check_do (void)
{
    if (is_automode ()) {//auto mode
        if (human_detected ()) {//human detected ?
            if (is_night ()) {//darkness ?
                turn_on_bulb ();
            } else {//
            }
        } else {//no human ?
            turn_off_bulb ();
        }
    } else {//manual mode
        if (should_switch2auto ()) {//timeout in manual mode ?
            switch2auto ();
        }
    }
}
