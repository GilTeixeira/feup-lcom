#ifndef __TIMER_H
#define __TIMER_H

#include "i8254.h"

#define DEBUG 0

#define IRQ_SET_ERROR 2
#define IRQ_ENAB_ERROR 3
#define IRQ_DISAB_ERROR 4
#define IRQ_REM_ERROR 5
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

/** @defgroup timer timer
 * @{
 *
 * Functions for using the i8254 timers
 */

/**
 * @brief print error message when DEBUG is activated (= 1)
 *
 * @param msg The message to print
 */
void printErrors(char * msg);

/**
 * @brief Changes the operating frequency of a timer
 * 
 * Must not change the 3 LSBs (mode and BCD/binary) of the timer's control word.
 * @param timer Timer to configure. (Ranges from 0 to 2)
 * @param freq Timer operating frequency
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_set_frequency(unsigned char timer, unsigned long freq);

/**
 * @brief Subscribes and enables Timer 0 interrupts
 *
 * @return Returns bit order in interrupt mask; negative value on failure
 */
int timer_subscribe_int(void);

/**
 * @brief Unsubscribes Timer 0 interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_unsubscribe_int();

/**
 * @brief Timer 0 interrupt handler
 *
 * Increments counter
 */
void timer_int_handler();

/**
 * @brief Reads the input timer configuration via read-back command
 *
 * @param timer Timer whose config to read (Ranges from 0 to 2)
 * @param st    Address of memory position to be filled with the timer config
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_get_conf(unsigned char timer, unsigned char *st);

/**
 * @brief Shows timer configuration
 * 
 * Displays in a human friendly way, the configuration of a timer
 *  as read via the read-back command, by providing the values 
 *  (and meanings) of the different components of a timer configuration 
 *
 * @param conf configuration to display in human friendly way
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_display_conf(unsigned char conf);

/**
 * @brief Tests change of Timer O interrupt frequency
 *
 * Programs Timer 0 to generate interrupts with input frequency
 *
 * @param freq Frequency of interrupts to generate
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_test_time_base(unsigned long freq);

/**
 * @brief Tests Timer 0 interrupt handling
 *
 * Subscribes Timer 0 interrupts and prints a message once
 *  per second for the specified time interval
 *
 * @param time Length of time interval while interrupts are subscribed
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_test_int(unsigned long time);

/**
 * @brief Tests display of timer config
 *
 * Just calls timer_get_conf() followed by timer_display_conf()
 *
 * @param timer Timer whose config to read (Ranges from 0 to 2)
 * @return Return 0 upon success and non-zero otherwise
 */
int timer_test_config(unsigned char timer);

#endif /* __TIMER_H */
