#if !defined __INTERRUPT_H__
#define __INTERRUPT_H__

/**
 * PSW (Processor Status Word) Register, Bit addressable
 * +-----------------------------------------+
 * | CY | AC | F0 | RS1 | RS0 | 0V | USR | P |
 * +-----------------------------------------+
 * CY -- Carry flag
 * AC -- Assistant carry flag
 * F0 -- General Flag
 * RS1-- Registers group bit 1
 * RS0-- Registers group bit 0
 * OV -- Overflow bit
 * USR-- User defined bit
 * P  -- Parity check bit
 **/

/**
 * IE (Interruption Enable) Register, bit addressable
 * +-------------------------------------------+
 * | EA | - | ET2 | ES | ET1 | EX1 | ET0 | EX0 |
 * +----+---+-----+----+-----+-----+-----+-----+
 * |  1 | - |  0  |  0 |  0  |  1  |  1  |  1  |
 * +-------------------------------------------+
 *
 * EA  -- Enable all
 * ET2 -- Enable timer2
 * ES  -- Enable serial port
 * ET1 -- Enable timer1
 *
 **/
#define disable_int() EA = 0
#define enable_int() EA = 1
/**
 *  PCON (Power Control) Register (Non-bit addressable)
 *  +--------------------------------------------+
 *  | SMOD | - | - | - | GF1 | GF0 | PDWN | IDLE |
 *  +------+---+---+---+-----+-----+------+------+
 *  |  0   | 0 | 0 | 0 |  0  |  0  |  0   |   1  |
 *  +--------------------------------------------+
 *  SMOD -- Serial MOD, double baud rate if set
 *  GF1  -- General Flag 1
 *  GF0  -- General Flag 0
 *  PDWN -- Power down, both CPU and peripheral OSCI will be shutdown if set
 *  IDLE -- CPU will be shut down but peripheral OSCI still work if set
 *          and CPU will be waken up if interruption occurs
 **/
#define idle_cpu() PCON |= 0x01
/**
 * IP(Interruption Priority) Register (Bit addressable)
 * +--------------------------------------------+
 * | -- | -- | PT2 | PS | PT1 | PX1 | PT0 | PX0 |
 * +----+----+-----+----+-----+-----+-----+-----+
 * |  0 |  0 |  0  |  0 |  0  |  1  |  1  |  0  |
 * +--------------------------------------------+
 * PX0 -- Priority external 0, connected to Human sensor
 * PX1 -- Priority external 1, connected to Remote control
 * PT0 -- Internal Timer0
 *
 **/
#define init_int_levels() IP |= 0x12
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

void check_do (void);
#endif
