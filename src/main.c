#include <reg51.h>
#include <stdio.h>
#include "STC15W408AS.h"
#include "config.h"
#include "relay.h"
#include "interrupt.h"
#include "timer.h"
#include "sensor.h"
#include "remote_control.h"
#include "watch_dog.h"

sys_status data g_sysstatus;
sys_config data g_sysconfig;

void init (void)
{
    disable_int ();
    init_stack ();
    init_int ();
    init_int_levels ();
    init_config ();
    init_sys_status ();
    init_timer ();
    init_sensor ();
    init_remote_control ();
    enable_int ();
}
void run (void)
{
    for (;;) {
        init_wdt ();
        check_do ();
        clear_int_source ();
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
