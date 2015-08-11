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
#define enable_int()  EA = 1
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
 * 0x00 ~ 0x1F: 4 banks general registers (R0 ~ R7)
 * 0x20 ~ 0x2F: 16 Bytes (128 Bits) bit addressable memory
 *
 * SP default to 0x07 when power on
 * change to 0x30
 *
 **/
#define init_stack() SP = 0x30

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

void check_do (void);
#endif
