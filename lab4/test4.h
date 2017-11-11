#ifndef __TEST4_H
#define __TEST4_H

/**
 * @brief Types of States
 */
typedef enum {
	INIT, MBTTPRESSED, MOVUPRIGHT, MOVEDOWNLEFT, DONE
} state_t;

/**
 * @brief Types of Events
 */
typedef enum {
	BTTDOWN, BTTUP, MOVEDUPRIGHT, MOVEDDOWNLEFT, COMPLETED
} ev_type_t;

/**
 * @brief Struct to hold event information
 */
struct event_t {
	ev_type_t evType;
	short length_moved;
	short deltax;
	short deltay;
	short length_to_move;
};

/** @defgroup test4 test4
 * @{
 *
 * Functions for testing the kbd code
 */

/** 
 * @brief To test packet reception via interrupts 
 * 
 * Displays the packets received from the mouse
 * Exits after receiving the number of packets specified in argument
 * 
 * @param cnt Number of packets to receive and display before exiting
 * 
 * @return Return 0 upon success and non-zero otherwise
 */

int mouse_test_packet(unsigned short cnt);

/** 
 * @brief To test handling of more than one interrupt
 * 
 *  Similar test_packet() except that it 
 *  should terminate if no packets are received for idle_time seconds
 * 
 * @param idle_time Number of seconds without packets before exiting
 * 
 * @return Return 0 upon success and non-zero otherwise
 */

int mouse_test_async(unsigned short idle_time);

/** 
 * @brief To test PS/2 remote mode operation 
 * 
 * Configures the PS/2 to operate in remote mode
 * Periodically requests a packet from the mouse,
 * and displays the packets received from the mouse
 * Exits after receiving the number of packets specified in argument
 * 
 * @param period Period in milliseconds 
 * @param cnt Number of packets to receive and display before exiting
 * 
 * @return Return 0 upon success and non-zero otherwise
 */

int mouse_test_remote(unsigned long period, unsigned short cnt);

/** 
 * @brief To test state machine implementation
 * 
 *  Similar mouse_test_packet() except that it 
 *  should terminate if user moves the mouse continuously 
 *    with a positive slope
 * 
 * @param length minimum length of movement (mouse units)
 *  in the x-direction. If positive, upwards movement, otherwise
 *  downwards.
 *  
 * 
 * @return Return 0 upon success and non-zero otherwise
 */

int mouse_test_gesture(short length);

/**
 * @brief Clears Outbuff
 *
 * @return Return 0 upon success and non-zero otherwise
 */
unsigned long cleanOutBuf();

/**
 * @brief Get Variation of Mouse X coord
 *
 * @return Return Variation of Mouse X coord
 */
long getDeltaX();

/**
 * @brief Get Variation of Mouse Y coord
 *
 * @return Return Variation of Mouse Y coord
 */
long getDeltaY();

/**
 * @brief Checks if mouse right button is pressed
 *
 * @return Return 0 if it isnt and non-zero otherwise
 */
int isRightButtonPressed();

/**
 * @brief Process an Event
 */
void processEvent(struct event_t * mouseEvent);

/**
 * @brief Process a State Machine
 */
void processStateMachine(struct event_t * mouseEvent);

#endif /* __TEST_4.H */
