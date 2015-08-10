#if !defined __CONFIG_H__
#define __CONFIG_H__
typedef struct _sys_status {
    bit bdata e_relay;
    bit bdata h_sensor;
    bit bdata wdt;
    bit bdata bcontrol;
    unsigned int data l_sensor;
    unsigned int data remate_control;
}sys_status;

sys_status data g_systatus;
void init_config (void);
#endif
