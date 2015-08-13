#include <reg51.h>
#include "config.h"
#include "sensor.h"
#include "relay.h"
#include "bulb.h"
#include "eprom.h"
#include "watch_dog.h"


/**
 * External 0 Interrupt
 *
 * Addr: 0x003
 **/
void EX0_ISR (void) interrupt 0 using 1
{
}

/**
 * Timer 0 Interrupt
 *
 * Addr: 0x00B
 **/
void timer0_ISR (void) interrupt 1 using 0
{
    static unsigned char data counter = 0x14;
    //disable_int ();
    stop_timer (0);
    reload_timer (0, TIMER_25MSH, TIMER_25MSL);
    run_timer (0);
    //enable_int ();
    //
    if (!--counter) {//1 second elapsed ?
        counter = 0x14;
        mark_status (second_flag, 1);
        mark_status (int_source, get_status (int_source) | INT_TIMER0);
        //init_wdt ();//reset watch dog
    }
}
/**
 * Serial Port Interrupt
 *
 **/
void ES_ISR (void) interrupt 3 using 1
{

}
/**
 *
 * A/D Convertion Interrupt
 *
 **/
void ADC_ISR (void) interrupt 4 using 1
{
}

/**
 *
 * Low voltage detection Interrupt
 *
 **/
void LVD_ISR (void) interrupt 5 using 1
{
    mark_status (low_v, 1);
}

void update_sys_status ()
{
    //mark_status (l_sensor, read_light_intensity_sensor ());
    mark_status (h_sensor, read_human_sensor ());
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
