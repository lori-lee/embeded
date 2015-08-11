#if !defined __CONFIG_H__
#define __CONFIG_H__
typedef struct _sys_status {
    bit bdata mode;//0 --auto mode, 1 --manual mode
    bit bdata e_relay;//0 --relay off, 1 --relay on
    bit bdata h_sensor;//0 --no human detected, 1 -- the opposite
    bit bdata wdt;//0 -- watch dog disabled, 1 -- enabled
    bit bdata bcontrol;//
    //
    bit bdata second_flag;//1 second ?
    unsigned char data int_source;//0x1 --timer0, 0x2 --human sensor, 0x4 --light intensity sensor, 0x8 -- remoate control
    unsigned int data l_sensor;//the value of light intensity
    unsigned int data remote_control;//
    unsigned int secs_elapsed;//seconds elapsed in manual mode
}sys_status;
//
volatile sys_status data g_sysstatus;

#define mark_mode_status(value)             g_sysstatus.mode    = value
#define mark_e_relay_status(value)          g_sysstatus.e_relay = value
#define mark_h_sensor_status(value)         g_sysstatus.h_sensor= value
#define mark_wdt_status(value)              g_sysstatus.wdt     = value
#define mark_int_source_status(value)       g_sysstatus.int_source = value
#define mark_l_sensor_status(value)         g_sysstatus.l_sensor   = value
#define mark_remote_control_status(value)   g_sysstatus.remote_control = value
#define mark_second_flag_status(value)      g_sysstatus.second_flag    = value
#define mark_secs_elapsed(value)            g_sysstatus.secs_elapsed   = value

#define mark_status(member,value)   mark_##member##_status (value)

#define get_mode_status()             g_sysstatus.mode
#define get_e_relay_status()          g_sysstatus.e_relay
#define get_h_sensor_status()         g_sysstatus.h_sensor
#define get_wdt_status()              g_sysstatus.wdt
#define get_int_source_status()       g_sysstatus.int_source
#define get_l_sensor_status()         g_sysstatus.l_sensor
#define get_remote_control_status()   g_sysstatus.remote_control
#define get_secs_elapsed()            g_sysstatus.secs_elapsed
#define get_status(member) get_##member##_status ()

typedef struct _sys_config {
    unsigned int light_threshold;//min light intensity
    unsigned int m2a_mode_threshold;//timeout (seconds) before switch manual mode to auto-mode
}sys_config;
//
volatile sys_config data g_sysconfig;

#define mark_light_threshold_config(value)       g_sysconfig.light_threshold    = value
#define mark_m2a_mode_threshold_config(value)    g_sysconfig.m2a_mode_threshold = value

#define mark_config(member,value) mark_##member##_config (value)

#define get_light_threshold_config()       g_sysconfig.light_threshold
#define get_m2a_mode_threshold_config()    g_sysconfig.m2a_mode_threshold

#define get_config(member) mark_##member##_config ()

#define is_night()      (get_status (l_sensor) < get_config (light_threshold))
#define is_automode()   (0 == get_status (mode))
#define is_manualmode() (!is_automode ())

#define human_detected()        get_status (h_sensor)
#define should_switch2auto()    (get_status (secs_elapsed) >= get_config (m2a_mode_threshold))
#define inc_secs_elpased()      ++get_status (secs_elapsed)
#define switch2auto()           mark_status (mode, 0)
#define switch2manual()   do {\
    mark_status (mode, 1);\
    mark_status (secs_elapsed, 0);\
}while (0)


void init_config (void);
#endif
