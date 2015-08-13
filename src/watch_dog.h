#if !defined __WATCH_DOG_H__
#define __WATCH_DOG_H__

#define init_wdt() do {\
    WDT_CONTR &= 0x3F;\
    mark_status (wdt, 0);\
}while (0)
#endif
