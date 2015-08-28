#if !defined __RELAY_H__
#define __RELAY_H__
#include "config.h"
#include "STC15W408AS.h"

#define init_relay() set_IO_mode (1, 1, 0x1)
#define read_relay_status() (P1 & 0x20)
#define set_relay_status() (P1 |= 0x20)

#define delay_timeoout() (get_status (delay) <= 0)
#endif
