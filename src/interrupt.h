#if !defined __INTERRUPT_H__
#define __INTERRUPT_H__

#define disable_int() EA=0
#define init_int_levels()
#define enable_int() EA=1
#define idle_cpu() PCON=0x4

typedef struct _interruptH {
}INTH;

void check_do (void);
#endif
