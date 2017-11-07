#ifndef __KBD_H
#define __KBD_H


#define IRQ_MOUSE_SET_ERROR 26
#define IRQ_MOUSE_ENAB_ERROR 27
#define IRQ_MOUSE_DISAB_ERROR 28
#define IRQ_MOUSE_REM_ERROR 29


//TO DO:ALTERAR
#define KBD_SYS_IN_ERROR 29



int mouse_subscribe_int(void);

int mouse_unsubscribe_int();

unsigned long readByte();

void mouse_handler();

int print_packets();

int enable_stream_mode();

#endif
