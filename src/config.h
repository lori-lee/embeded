
/************************LAYOUT************************
 *                    +---------+
 *                    | E-Relay |
 *                    +----+----+      +--------+
 *                         |   +-------| SWITCH |
 *                      I/O|   |  INT0 +--------+
 *                         |   | 
 * +--------+   I/O   +----+----+  ADC +--------+
 * |H-SENSOR|---------|STC15xCPU|------|L-SENSOR|
 * +--------+         +----+----+      +--------+
 *                         |
 *                         |ES(Serial Interruption) + I/O
 *                         |
 *                 +-------+------+
 *                 |Remote Control|
 *                 +--------------+
 *
 *
 *
 ******************************************************/

#if !defined __CONFIG_H__
#define __CONFIG_H__
//INT Source
#define  INT_TIMER0 0x1
#define  INT_LSENOR 0x2
#define  INT_RTCTR  0x4
#define  INT_SWITCH 0x8
/**
 * Current system status
 *
 **/
typedef struct _sys_status {
    unsigned char low_v: 1;//voltage too low ?
    unsigned char mode: 1;//0 --auto mode, 1 --manual mode
    unsigned char e_relay: 1;//0 --relay off, 1 --relay on
    unsigned char h_sensor: 1;//0 --no human detected, 1 -- the opposite
    unsigned char wdt: 1;//0 -- watch dog disabled, 1 -- enabled
    //
    unsigned char second_flag: 1;//1 second ?
    unsigned char manual_save_flag: 1;//SAVE from Remote control?

    unsigned char int_source;//0x1 --timer0, 0x2 --light intensity sensor, 0x4 -- remote control, 0x8 -- Switch
    unsigned int l_sensor;//the value of light intensity
    unsigned int secs_elapsed;//seconds elapsed in manual mode
    unsigned char hour;//for auto turn off bulk when timeout
    unsigned char minute;//for auto turn off bulk when timeout
}sys_status;
//
volatile sys_status data g_sysstatus;

#define mark_low_v_status(value)            g_sysstatus.low_v   = value
#define mark_mode_status(value)             g_sysstatus.mode    = value
#define mark_e_relay_status(value)          g_sysstatus.e_relay = value
#define mark_h_sensor_status(value)         g_sysstatus.h_sensor= value
#define mark_wdt_status(value)              g_sysstatus.wdt     = value
#define mark_int_source_status(value)       g_sysstatus.int_source = value
#define mark_l_sensor_status(value)         g_sysstatus.l_sensor   = value
#define mark_remote_control_status(value)   g_sysstatus.remote_control = value
#define mark_second_flag_status(value)      g_sysstatus.second_flag    = value
#define mark_manual_save_flag_status(value) g_sysstatus.manual_save_flag = value
#define mark_secs_elapsed_status(value)     g_sysstatus.secs_elapsed   = value
#define mark_hour_status(value)             g_sysstatus.hour  = value
#define mark_minute_status(value)           g_sysstatus.minute= value

#define mark_status(member,value)   mark_##member##_status (value)
#define clear_int_source()          g_sysstatus.int_source = 0

#define get_low_v_status()            g_sysstatus.low_v
#define get_mode_status()             g_sysstatus.mode
#define get_e_relay_status()          g_sysstatus.e_relay
#define get_h_sensor_status()         g_sysstatus.h_sensor
#define get_wdt_status()              g_sysstatus.wdt
#define get_int_source_status()       g_sysstatus.int_source
#define get_l_sensor_status()         g_sysstatus.l_sensor
#define get_remote_control_status()   g_sysstatus.remote_control
#define get_secs_elapsed_status()     g_sysstatus.secs_elapsed
#define get_hour_status()             g_sysstatus.hour
#define get_minute_status()           g_sysstatus.minute

#define get_status(member) get_##member##_status ()

#define is_voltage_low() get_status(low_v)
#define is_relay_on() get_status (e_relay)
#define is_relay_off() !get_status (e_relay)
#define need_save_config() get_status (manual_save_flag)

/**
 *
 * System configuration
 *
 **/
typedef struct _sys_config {
    unsigned int light_threshold;//min light intensity
    unsigned int m2a_mode_threshold;//timeout (seconds) before switch manual mode to auto-mode
    unsigned char hour;//
    unsigned char minute;//
}sys_config;
//
volatile sys_config data g_sysconfig;

#define mark_light_threshold_config(value)       g_sysconfig.light_threshold    = value
#define mark_m2a_mode_threshold_config(value)    g_sysconfig.m2a_mode_threshold = value
#define mark_hour_config(value)                  g_sysconfig.hour  = value
#define mark_minute_config(value)                g_sysconfig.minute= value

#define mark_config(member,value) mark_##member##_config (value)

#define get_light_threshold_config()       g_sysconfig.light_threshold
#define get_m2a_mode_threshold_config()    g_sysconfig.m2a_mode_threshold
#define get_hour_config()                  g_sysconfig.hour
#define get_minute_config()                g_sysconfig.minute

#define get_config(member) mark_##member##_config ()

#define is_dark()       (get_status (l_sensor) < get_config (light_threshold))
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


extern void init_config (void);
#endif
