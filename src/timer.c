#include <reg51.h>
#include "config.h"
#include "timer.h"
#include "watch_dog.h"

void timer0_ISR (void) interrupt 1 using 0
{
    static unsigned char data counter = 0x14;
    //disable_int ();
    stop_timer (0);
    reload_timer (0, TIMER_25MSH, TIMER_25MSL);
    run_timer (0);
    //enable_int ();
    //
    --counter;
    if (!counter) {//1 second elapsed ?
        counter = 0x14;
        mark_status (second_flag, 1);
        mark_status (int_source, get_status (int_source) | INT_TIMER0);
        //init_wdt ();//reset watch dog
    }
}
