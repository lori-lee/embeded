#if !defined __WATCH_DOG_H__
#define __WATCH_DOG_H__

#include "config.h"
#include "STC15W408AS.h"

/**
 * WDT_CONTR (Addr: 0x0C1)
 * +-------------------------------------------------------------+
 * | WDT_FLAG | - | EN_WDT | CLR_WDT | IDL_WDT | PS2 | PS1 | PS0 |
 * +-------------------------------------------------------------+
 * WDT_FLAG   -- Flag of reset by watch dog, when counter down over, set by hardware,
 *               need to be reset by software
 * EN_WDT     -- Enable Watch Dog, cannot be disable by software if enabled
 * CLR_WDT    -- Clear watch dog timer
 * IDLE_WDT   -- whether WDT should go on working when CPU is in IDLE mode
 * PS2  PS1 PS0 (Prescale)
 *  0    0   0      2
 *  0    0   1      4
 *  0    1   0      8
 *  0    1   1     16
 *  1    0   0     32
 *  1    0   1     64
 *  1    1   0     128
 *  1    1   1     256
 *
 * Overflow timerout: N * Prescale * (1 << 15) / SysClckFreq
 * N = 12, 6, 1 (for 12T, 6T, 1T)
 **/

#define init_wdt() do {\
    WDT_CONTR &= 0x3F;\
    mark_status (wdt, 0);\
}while (0)
#define clear_wdt()       WDT_CONTR |= 0x10
#endif
