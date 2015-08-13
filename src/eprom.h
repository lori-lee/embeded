#if !defined __EPROM_H__
#define __EPROM_H__

#include "config.h"
//Idle mode
#define IAP_CMD_ST  0
//Read by byte
#define IAP_CMD_RD  1
//Write by byte
#define IAP_CMD_WT  2
//Erase sector
#define IAP_CMD_ER  3

#define delay(n) for(int i = 0; i < n; ++i) _nop_();
#define CYCLES_RD 2
#define CYCLES_WT 1320

#define can_iap() get_status (low_v)
#define enable_iap() IAP_CONTR = 0x80
#define disable_iap() IAP_CONTR&= 0x7F
#define execute_iap(type) do {IAP_TRIG = 0x5A; IAP_TRIG = 0xA5;delay (CYCLES_##type);}while(0)

#define is_iap_fail() IAP_CONTR &= ~0x10
static void turn_off_iap (void);

extern bit write_byte (unsigned char byte, unsigned int addr);
extern void save_sys_config (void);
#endif
