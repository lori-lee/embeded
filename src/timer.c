#include "config.h"
#include "watch_dog.h"

extern sys_status g_sysstatus;
extern sys_config g_sysconfig;
void timer0_ISR (void) interrupt 1 using 0
{
    volatile static unsigned char data counter = 0x14;
    //disable_int ();
    stop_timer (0);
    reload_timer (TIMER_50MS);
    run_timer (0);
    //enable_int ();
    //
    --counter;
    if (!counter) {//1 second elapsed ?
        counter = 0x14;
        mark_status (second_flag, 1);
        init_wdt ();//reset watch dog
    }
}
