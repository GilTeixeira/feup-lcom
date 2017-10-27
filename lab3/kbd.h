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


int kbd_subscribe_int(void);

int kbd_unsubscribe_int(void);

unsigned long readcode();

unsigned long polling();

int printcode(unsigned long code, int isSecondByte);

int kbd_handler();

int WriteCommandByte(unsigned long port, unsigned long cmd);

unsigned long ReadCommandByte();

extern unsigned char kbd_asm_handler();
