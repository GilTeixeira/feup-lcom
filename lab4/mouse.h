#ifndef __MOUSE_H
#define __MOUSE_H


#define IRQ_MOUSE_SET_ERROR 26
#define IRQ_MOUSE_ENAB_ERROR 27
#define IRQ_MOUSE_DISAB_ERROR 28
#define IRQ_MOUSE_REM_ERROR 29
#define MOUSE_WRITE_CMD_ERROR 30
#define MOUSE_SYS_OUT_ERROR 31
#define MOUSE_SUB_ERROR 32
#define MOUSE_UNSUB_ERROR 33
#define CLEAN_OUTBUFF_ERROR 34
#define ENAB_STREAM_MODE_ERROR 35




//#define IRQ_MOUSE_REM_ERROR 30
//#define IRQ_MOUSE_REM_ERROR 30


//TO DO:ALTERAR
//#define KBD_SYS_IN_ERROR 29

extern int fullPacket;


int mouse_subscribe_int(void);

int mouse_unsubscribe_int();

unsigned long readByte();

void mouse_handler();
int mouse_subscribe_Exc_int(void);

int print_packets();

int enable_stream_mode();
int mouseWriteCommandByte(unsigned long cmd);
unsigned long mouseReadOutput();
long convertNumber(char number, unsigned long msb);

#endif

