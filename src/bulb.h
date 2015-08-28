#if !defined __BULB_H__
#define __BULB_H__

#include "config.h"

#define turn_on_bulb()    P1 |= 0x02
#define turn_off_bulb()   P1 &= ~0x02
#endif
