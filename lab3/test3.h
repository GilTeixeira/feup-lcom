#ifndef __TEST3_H
#define __TEST3_H

#include <minix/syslib.h>


/** @defgroup test3 test3
 * @{
 *
 * Functions for testing the kbd code
 */

/**
 * @brief Uses Sys_inb and increments counter
 *
 * @return Return 0 upon success and non-zero otherwise
 */

#ifdef LAB3
int sys_inb_cnt(port_t port, unsigned long* byte);
#else
#define sys_inb_cnt(p,q) sys_inb(p,q)
#endif


/** 
 * @brief To test reading of scancode via KBD interrupts 
 * 
 * Displays the scancodes received from the keyboard
 * Exits upon release of the ESC key
 * 
 * @param asm Which IH to use: if 0, in C, otherwise in assembly
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbd_test_scan(unsigned short assembly);

/**
 * @brief To test reading of scancodes via polling
 * 
 * Displays the scancodes received from the keyboard
 * Exits upon release of the ESC key
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbd_test_poll();

/** 
 * @brief To test handling of more than one interrupt
 * 
 *  Similar to kbd_test_scan() except that it 
 *  should terminate also if no scancodes are received for n seconds
 * ou seja com o esc ou tempo
 * @param n Number of seconds without scancodes before exiting
 * 
 * @return Return 0 upon success and non-zero otherwise
 */
int kbd_test_timed_scan(unsigned short n);

#endif /* __TEST3_H */
