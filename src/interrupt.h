#if !defined __INTERRUPT_H__
#define __INTERRUPT_H__
/**
 * Interruption vector layout
 * +----------------------------------+-----------+
 * | IE enable bit index | INT Source |  Address  |
 * +---------------------+------------+-----------+
 * |          0          | External 0 |  0x0003   |
 * +---------------------+------------+-----------+
 * |          1          |   Timer0   |  0x000B   |
 * +---------------------+------------+-----------+
 * |          2          | External 1 |  0x0013   |
 * +---------------------+------------+-----------+
 * |          3          |   Timer1   |  0x001B   |
 * +---------------------+------------+-----------+
 * |          4          | Serial INT |  0x0023   |
 * +---------------------+------------+-----------+
 * |          5          |   Timer 2  |  0x002B   |
 * +----------------------------------+-----------+
 *
 *
 **/
/**
 * PSW (Processor Status Word) Register, Bit addressable
 * +-----------------------------------------+
 * | CY | AC | F0 | RS1 | RS0 | 0V | USR | P |
 * +-----------------------------------------+
 * CY -- Carry flag
 * AC -- Assistant carry flag
 * F0 -- General Flag
 * RS1-- Registers Set (Group) bit 1
 * RS0-- Registers Set (Group) bit 0
 * OV -- Overflow bit
 * USR-- User defined bit
 * P  -- Parity check bit
 **/

/**
 * IE (Interruption Enable) Register, bit addressable
 *   7     6      5     4     3     2     1     0
 * +-----------------------------------------------+
 * | EA | ELVD | EADC | ES | ET1 | EX1 | ET0 | EX0 |
 * +----+------+------+----+-----+-----+-----+-----+
 * |  1 |   1  |  0   |  1 |  0  |  0  |  1  |  1  |
 * +-----------------------------------------------+
 *
 * EA  -- Enable all
 * ELVD-- Enable Low Voltage Detection Interruption
 * EADC-- Enable ADC Interruption
 * ES  -- Enable serial port
 * ET1 -- Enable timer1
 *
 * IE2 (Non bit addressable)
 * +---------------------------------------------+
 * | - | ET4 | ET3 | ES4 | ES3 | ET2 | ESPI | ES2|
 * +---------------------------------------------+
 * ET4   -- Enable Timer 4
 * ET3   -- Enable Timer 3
 * ES4   -- Enable Serial 4
 * ES3   -- Enable Serial 3
 * ET2   -- Enable Timer 2
 * ESPI  -- Enable SPI
 * ES2   -- Enable Serial 2
 *
 **/
#define disable_int() EA = 0
#define enable_int()  EA = 1

#define enable_LVDP_int()  IE |= 0x40
#define disable_LVDP_int() IE &= ~0x40

#define enable_ADC_int()   IE |= 0x20
#define disable_ADC_int()  IE &= ~0x20 

#define enable_switch_int()  IE |= 0x04
#define disable_switch_int() IE &= ~0x04

#define init_int()   IE = 0x53

/**
 *  PCON (Power Control) Register (Non-bit addressable)
 *  +-----------------------------------------------------+
 *  | SMOD | SMOD0 | LVDF | POF | GF1 | GF0 | PDWN | IDLE |
 *  +------+-------+------+-----+-----+-----+------+------+
 *  |  0   |   0   |   0  |  0  |  0  |  0  |  0   |   1  |
 *  +-----------------------------------------------------+
 *  SMOD -- Serial MOD, double baud rate if set
 *  GF1  -- General Flag 1
 *  GF0  -- General Flag 0
 *  PDWN -- Power down, both CPU and peripheral OSCI will be shutdown if set
 *  IDLE -- CPU will be shut down but peripheral OSCI still work if set
 *          and CPU will be waken up if interruption occurs
 **/
#define idle_cpu() PCON &= 0x81
/**
 * IP(Interruption Priority) Register (Bit addressable)
 * +-------------------------------------------------+
 * | PPCA | PLVD | PADC | PS | PT1 | PX1 | PT0 | PX0 |
 * +------+------+------+----+-----+-----+-----+-----+
 * |  0   |  1   |   0  |  1 |  0  |  1  |  0  |  1  |
 * +-------------------------------------------------+
 * PX0 -- Priority external 0, connected to Remote control(infared)
 * PX1 -- Priority external 1, connected to light intensity sensor
 * PS  -- Priority Serial Port, connected to manual switch
 * PT0 -- Internal Timer0
 * PADC-- Priority ADC
 * PLVD-- Priority Low Voltage Dectection
 * PPCA-- Priority PCA
 *
 * IP2 (Non bit addressable)
 * +----------------------------------------------+
 * | - | - | - | PX4 | PPWMFD | PPWM | PSPI | PS2 |
 * +----------------------------------------------+
 * PX4    -- Priority External 4
 * PPWMFD -- Priority PWM abnormal dectecting Interruption
 * PPWM   -- Priority PWM
 **/
#define init_int_levels() do {\
    IP  &= 0x55;\
    IP2 &= 0;\
}while (0)

/**
 * 0x00 ~ 0x1F: 4 banks general registers (R0 ~ R7)
 * 0x20 ~ 0x2F: 16 Bytes (128 Bits) bit addressable memory
 *
 * SP default to 0x07 when power on
 * change to 0x60
 *
 **/
#define init_stack() SP = 0x60

/**
 * UART
 * SCON (Serial Port Control) Register, bit addressable
 * +---------------------------------------------+
 * | SM0 | SM1 | SM2 | REN | TB8 | RB8 | TI | RI |
 * +---------------------------------------------+
 * SM0  -- Serial Mode bit 0
 * SM1  -- Serial Mode bit 1
 * SM2  -- Multi-machine comunication enable bit.
 *         0  if Mode == 0
 *         1  if mode == 1 and stop bit received
 *         1  if mode == 2 or 3, and the 9th bit received is 1
 * REN  -- Serical receive enable bit
 * TB8  -- the 9th bit to be sent when mode == 2 or 3
 * RB8  -- no meaning when mode == 0
 *         the stop bit received when mode == 1 
 *         the 9th bit received when mode == 2 or 3
 * TI   -- Serial Transmit Interruption flag bit, reset by CPU (software)
 * RI   -- Receive Interruption flag bit, reset by CPU (software)
 *
 **/

/**
 * ADC_CONTR (ADC Control Register)
 *
 * +-------------------------------------------------------------------------+
 * | ADC_POWER | SPEED1 | SPEED0 | ADC_FLAG | ADC_START | CHS2 | CHS1 | CHS0 |
 * +-------------------------------------------------------------------------+
 * ADC_POWER   -- ACD Power Control Bit, 0: Turn off ADC power, verse the versa
 * ADC_FLAG    -- Flag of whether ADC finished, 1: finished, reset by software
 * ADC_START   -- 1: start ADC, 0: ADC finished.
 *
 **/

/**
 * AUXR (Auxiliary Register)
 * +------------------------------------------------------------------+
 * | T0x12 | T1x12 | UART_M0x6 | T2R | T2_CT | T2x12 | EXTRAM | S1ST2 |
 * +------------------------------------------------------------------+
 * T0x12    -- 0: Timer 0 Freq / 12 (Act as traditional 8051)
 *             1: Timer 0 Freq / 1  (12 times faster than traditional 8051)
 * T1x12    -- Similar to T0x12
 *
 **/

/**
 * WDT_CONTR
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


#define FREQ_OSI 24000000L
//T0x12 = 0, FREQ_OSI / 12, 24x10^6 / (12 * 40) = 5x10^4
//65535 - 5x10^4 = 15535
#define TIMER_25MSH 0x3C
#define TIMER_25MSL 0xAF

#define reload_timer(index,HV,LV) do {\
    TH##index = HV;\
    TL##index = LV;\
}while (0)
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
extern void check_do (void);
#endif
