void timer0_ISR (void) interrupt 1 using 0
{
    static unsigned char data counter = 0x14;
    disable_int ();
    reload_timer (TIMER_50MS);
    enable_int ();
    //
    init_wdt ();//reset watch dog
    --counter;
    if (!counter) {//1 second elapsed ?
        counter = 0x14;
        if (get_status (mode)) {
            if (get_status (l_sensor) > get_config (light_threshold)) {
                mark_status (secs_elapsed) = get_status (secs_elapsed) - 1;
                return ;
            }
        }
        reset_light_intensity_counter ();
    }
}
