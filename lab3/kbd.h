#include "i8042.h"
#include "i8254.h"
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <minix/sysutil.h>
#include <minix/driver.h>
#include <minix/drivers.h>


#ifdef LAB3
int sys_inb_cnt(port_t port, unsigned long* byte);
#else
#define sys_inb_cnt(p,q) sys_inb(p,q)
#endif


#define IRQ_KBD_SET_ERROR 16
#define IRQ_KBD_ENAB_ERROR 17
#define IRQ_KBD_DISAB_ERROR 18
#define IRQ_KBD_REM_ERROR 19


#define TIMER_CONF_ERROR 6
#define SYS_OUT_ERROR 7
#define SYS_IN_ERROR 8
#define TIMER_SUB_ERROR 9
#define TIMER_UNSUB_ERROR 10
#define TIMER_GET_CONF_ERROR 11
#define TIMER_DISPLAY_CONF_ERROR 12
#define FREQ_NEG_ERROR 13
#define FREQ_OVERFLOW_ERROR 14
#define INPUT_NEG_ERROR 15

unsigned long globalCode;


/**
 * @brief Subscribes Keyboard interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int kbd_subscribe_int(void);


/**
 * @brief Unsubscribes Keyboard interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int kbd_unsubscribe_int(void);

unsigned long readCode();

unsigned long polling();

int printcode(unsigned long code, int isSecondByte);

void kbd_handler();

int WriteCommandByte(unsigned long port, unsigned long cmd);

unsigned long ReadCommandByte();

extern unsigned char kbd_asm_handler();
