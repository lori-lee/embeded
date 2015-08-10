#if !defined __CONFIG_H__
#define __CONFIG_H__
typedef struct _sys_status {
    bit bdata mode;//0 --auto mode, 1 --manual mode
    bit bdata e_relay;//0 --relay off, 1 --relay on
    bit bdata h_sensor;//0 --no human detected, 1 -- the opposite
    bit bdata wdt;//0 -- watch dog disabled, 1 -- enabled
    bit bdata bcontrol;//
    unsigned char data int_source;//0x1 --timer0, 0x2 --human sensor, 0x4 --light intensity sensor, 0x8 -- remoate control
    unsigned int data l_sensor;//the value of light intensity
    unsigned int data remate_control;//
}sys_status;

typedef struct _sys_config {
    unsigned int light_threshold;//min light intensity
    unsigned int m2a_mode_threshold;//timeout (seconds) before switch manual mode to auto-mode
}sys_config;
sys_status data g_systatus;
void init_config (void);
#endif
