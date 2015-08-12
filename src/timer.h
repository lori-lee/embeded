#if !defined __TIMER_H__
#define __TIMER_H__
#define TIMER_50MS 0xAAFF
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

/**
 * TCON (Timer Control) Register, bit addressable
 * +-----------------------------------------------+
 * | TF1 | TR1 | TF0 | TR0 | IE1 | IT1 | IE0 | IT0 |
 * +-----+-----+-----+-----+-----+-----+-----+-----+
 * |  -  |  0  |  -  |  1  |  -  |  1  |  -  |  1  |
 * +-----------------------------------------------+
 * TF1  -- Timer 1 overflow interruption flag, reset by CPU(software)
 * TR1  -- Timer 1 Running flag, timer 1 start working if set
 * TF0  -- Similar to TF1
 * TR0  -- Similar to TR1
 * IE1  -- Interruption external 1, will be set if interruption occurs,
 *         and reset automatically by hardware
 * IT1  -- Interruption external 1 trigger style control bit, triggered when
 *         voltage hops if set, else triggered when low voltage detected.  
 * IE0  -- Similar to IE1
 * IT0  -- Similar to IT1
 *
 **/
#define run_timer(index)   TR##index = 1
#define stop_timer(index)  TR##index = 0
#define clear_timer(index) TF##index = 0

/**
 * TMOD (Timer mode) Register, Non-bit addressable
 * +---------------------------------------------+
 * | GATE | C/T | M1 | M0 | GATE | C/T | M1 | M0 |
 * +------+-----+----+----+------+-----+----+----+
 * |      Timer 1         |      Timer 0         |
 * +---------------------------------------------+
 * GATE   -- if set, Timer 1 works only if TR1=1 and INT=1
 *           else, works if TR1 = 1   
 * C/T    -- Counter/Timer, C/T = 1, works as counter
 *           else works as timer
 * M1     -- Mode bit 1
 * M0     -- Mode bit 0
 * M1 M0
 * 0  0   13 bit, when counter == 0, interruption occurs
 * 0  1   16 bit, when counter == 0, interruption occurs
 * 1  0   auto reload, lower 8 bits -- counter (TL0/TL1)
 *                     higher 8 bits-- reload value (TH0/TH1)
 * 1  1   timer0 works as 2 timers, (TH0/TL0).
 *
 **/
//Only use timer0 to work as timer
#define init_timer() TMOD &= 0x01

#endif
