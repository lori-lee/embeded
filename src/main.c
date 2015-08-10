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
    enable_int ();
}
void run (void)
{
    for (;;) {
        check_do ();
        idle_cpu (); 
    }
}
void main (void)
{
    init ();
    run ();
}
