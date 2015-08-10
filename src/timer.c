void timer0_ISR (void) interrupt 1 using 0
{
    disable_int ();
    reload_timer (TIMER_50MS);
    enable_int ();
}
