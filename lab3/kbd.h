#ifndef __KBD_H
#define __KBD_H

#define KBD_SYS_IN_ERROR 0xFFE //Error Reading Code
#define KBD_IN_CMD_ERROR 0xFFF //Error Reading Command Byte

#define IRQ_KBD_SET_ERROR -16
#define IRQ_KBD_ENAB_ERROR -17
#define IRQ_KBD_DISAB_ERROR -18
#define IRQ_KBD_REM_ERROR -19

#define KBD_SYS_OUT_ERROR 20
#define KBD_POLLING_ERROR 21
#define KBD_TEST_SCAN_ERROR 22
#define KBD_SUB_ERROR 23
#define KBD_UNSUB_ERROR 24
#define KBD_WRITE_CMD_BYTE_ERROR 25

/*
 #define SYS_OUT_ERROR 7
 #define SYS_IN_ERROR 8
 #define TIMER_SUB_ERROR 9
 #define TIMER_UNSUB_ERROR 10
 #define TIMER_GET_CONF_ERROR 11
 #define TIMER_DISPLAY_CONF_ERROR 12
 #define FREQ_NEG_ERROR 13
 #define FREQ_OVERFLOW_ERROR 14
 #define INPUT_NEG_ERROR 15
 */

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

/**
 * @brief Read Code from Keyboard with interrupts
 *
 * @return Return code upon success and KBD_SYS_IN_ERROR otherwise
 */
unsigned long readCode();

/**
 * @brief Read Code from Keyboard with polling
 *
 * @return Return code upon success and KBD_SYS_IN_ERROR otherwise
 */
unsigned long polling();

/**
 * @brief Shows Code Read
 *
 * Displays in a human friendly way, the Make and Break Code
 *
 * @param code the Code to be printed
 * @param isSecondByte 1 if is the Second Byte and 0 otherwise
 * @return Return 0 upon success and non-zero otherwise
 */
int printcode(unsigned long code, int isSecondByte);

/**
 * @brief Keyboard interrupt handler
 *
 * Increments counter
 */
void kbd_handler();

/**
 * @brief Write CommandByte and Arguments to the port
 *
 * @param port the port to be sent the code
 * @param cmd the cmd or the argument
 * @return Return 0 upon success and non-zero otherwise
 */
int WriteCommandByte(unsigned long port, unsigned long cmd);

/**
 * @brief Read current CommandByte
 *
 * @return Return the Command Byte
 */
unsigned long ReadCommandByte();

/**
 * @brief Keyboard interrupt handler in assembly
 *
 * Increments counter
 */
extern unsigned char kbd_asm_handler();

#endif
