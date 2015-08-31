#include <reg51.h>
#include "config.h"
#include "interrupt.h"
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
    mark_status (mode, 1);

    if (is_relay_on ()) turn_off_bulb ();
    else turn_on_bulb ();
    mark_status (e_relay, get_status (e_relay) ^ 1);

    set_int_source (INT_SWITCH);
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
        set_int_source (INT_TIMER0);
        //init_wdt ();//reset watch dog
    }
}
/**
 * Serial Port Interrupt
 *
 **/
void ES_ISR (void) interrupt 4 using 1
{
    set_int_source (INT_RTCTR);
}
/**
 *
 * A/D Convertion Interrupt
 *
 **/
void ADC_ISR (void) interrupt 5 using 1
{
    if (0 == CLK_DIV & ~0x20) {//Or PCON2.5(ADRJ == 0)
        mark_status (ADC10bit, 0x8000 + (ADC_RES << 2) + (ADC_RESL & 4));
    } else {//ADRJ == 1
        mark_status (ADC10bit, 0x8000 + ((ADC_RES & 4) << 8) + ADC_RESL);
    }
    set_int_source (INT_ADC);
}

/**
 *
 * Low voltage detection Interrupt
 *
 **/
void LVD_ISR (void) interrupt 6 using 1
{
    mark_status (low_v, 1);
    clear_LVD_int_flag ();
    set_int_source (INT_LVD);
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
                mark_status (e_relay, 1);
                mark_status (delay, get_config (delay));//Reset count down
            } else {//
                //DO NOTHING
            }
        } else {//no human ?
            if (get_status (second_flag)) {
                dec_delay ();
                if (delay_timeout ()) {
                    turn_off_bulb ();
                    mark_status (e_relay, 0);
                }
            }
        }
    } else {//manual mode ?
        if (need_save_config ()) {
            save_sys_config ();
            mark_status (manual_save_flag, 0);
        }
        if (is_relay_off () && !is_dark ()) {
            if (get_status (second_flag)) {
                inc_secs_elapsed ();
                if (should_switch2auto ()) {//timeout in manual mode ?
                    switch2auto ();
                }
            }
        } else {
            mark_status (secs_elapsed, 0);
        }
        //
        if (manual_turn_on_bulb ()) {
            turn_on_bulb ();
            mark_status (e_relay, 1);
        } else if (manual_turn_off_bulb ()) {
            turn_off_bulb ();
            mark_status (e_relay, 0);
        }
    }
    if (get_status (second_flag)) {
        mark_status (second_flag, 0);
    }
    clear_int_source ();
}
