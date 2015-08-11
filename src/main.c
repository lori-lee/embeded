#include <reg51.h>
#include <stdio.h>
#include "config.h"
#include "relay.h"
#include "interrupt.h"
#include "timer.h"
#include "sensor.h"
#include "remote_control.h"
#include "watch_dog.h"
void init (void)
{
    disable_int ();
    init_int_levels ();
    init_config ();
    init_timer ();
    init_sensor ();
    init_remote_control ();
    init_wdt ();
    enable_int ();
}
void run (void)
{
    for (;;) {
        check_do ();
        idle_cpu (); 
    }
}

#define WDT_RST 0xAA
#define PWT_RST 0xBB
unsigned char xdata reset_type = PWT_RST;
void main (void)
{
    if (WDT_RST != reset_type) {
        init ();
    }

    run ();
}
