#if !defined __RELAY_H__
#define __RELAY_H__

#define read_relay_status() P1_1
#define delay_timeoout() (get_status (delay) <= 0)
#endif
