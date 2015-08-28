#include "STC15W408AS.h"
#include <intrins.h>
#include "eprom.h"

void turn_off_iap()
{
    IAP_CONTR = 0;
    IAP_CMD = 0;
    IAP_TRIG= 0;
    IAP_ADDRH = 0x80;
    IAP_ADDRL = 0x0;
}

bit write_byte (unsigned char byte, unsigned int addr)
{
    bit b;

    if (!can_iap ()) return 0;//Should not operate EEPROM when Voltage too low
    enable_iap ();
    IAP_DATA = byte;
    IAP_ADDRH= addr >> 8;
    IAP_ADDRL= addr << 8;
    IAP_CMD  = IAP_CMD_WT;

    execute_iap (WT);
    b = is_iap_fail ();
    turn_off_iap ();

    return ~b;
}

unsigned char read_byte (unsigned int addr)
{
    unsigned char byte;
    bit b;

    if (!can_iap ()) return 0;//Should not operate EEPROM when Voltage too low

    enable_iap ();
    IAP_ADDRH= addr >> 8;
    IAP_ADDRL= addr << 8;
    IAP_CMD  = IAP_CMD_RD;

    execute_iap (RD);
    
    byte = IAP_DATA;
    b = is_iap_fail ();
    turn_off_iap ();

    return byte;
}

void save_sys_config (void)
{
}
