#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8254.h"

int hook_id = 0;
int counter = 0;

int timer_subscribe_int(void) {

	int temp_hook_id = hook_id; // we create it in order to not change  hook_id during the call in sys_irqsetpolicy

	sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
	sys_irqenable(&hook_id);

	return BIT(temp_hook_id);
}

int timer_unsubscribe_int() {

	sys_irqdisable(&hook_id);
	sys_irqrmpolicy(&hook_id);

	return Ok;
}

void timer_int_handler() {
	counter++;
}

int timer_get_conf(unsigned char timer, unsigned char *st) {

	unsigned long stout;
	port_t timerport;
	unsigned long timerselect;

	switch (timer) {
	case 0: //timer 0
		timerport = TIMER_0;
		timerselect = TIMER_RB_SEL(0);
		break;
	case 1: //timer1
		timerport = TIMER_1;
		timerselect = TIMER_RB_SEL(1);
		break;
	case 2: //timer2
		timerport = TIMER_2;
		timerselect = TIMER_RB_SEL(2);
		break;
	default:
		printf("error: timer doesn't exist");
		return 1;
	}

	stout = TIMER_RB_CMD | timerselect | TIMER_RB_COUNT_;
	sys_outb(TIMER_CTRL, stout);
	sys_inb(timerport, (unsigned long int *) st);

	return Ok;
}

int timer_display_conf(unsigned char conf) {

	printf("\n Type of access: ");

	if ((conf & (TIMER_MSB | TIMER_LSB)) == (TIMER_LSB_MSB))
		printf("LSB followed by MSB \n");
	else if ((conf & (TIMER_MSB)) == TIMER_MSB)
		printf("MSB \n");
	else if ((conf & (TIMER_LSB)) == TIMER_LSB)
		printf("LSB \n");
	else printf("Undeterminable \n");

	printf("\n Operating mode");

	if ((conf & BIT(3)) == 0) {
		if ((conf & TIMER_RATE_GEN) == 0)
			if ((conf & BIT(1)) == 0)
				printf(" 0: INTERRUPT ON TERMINAL COUNT \n"); //000
			else
				printf(" 1: HARDWARE RETRIGGERABLE ONE-SHOT \n"); //001
		else
			if ((conf & BIT(1)) == 0)
			printf(" 2: RATE GENERATOR \n"); //010
		else
			printf(" 3: SQUARE WAVE MODE \n"); //011
	} else {
		if ((conf & TIMER_RATE_GEN) == 0) {

			if ((conf & BIT(1)) == 0)
				printf(" 4: SOFTWARE TRIGGERED STROBE \n"); //100
			else
				printf(" 5: HARDWARE TRIGGERED STROBE (RETRIGGERABLE)  \n"); //101
		} else {
			if ((conf & BIT(1)) == 0)
				printf(" 2: RATE GENERATOR \n"); //110
			else
				printf(" 3: SQUARE WAVE MODE \n"); //111
		}
	}

	printf("\n Counting mode: ");

	if ((conf & BIT(0)) == 0)
		printf("Binary \n \n");
	else
		printf("BCD \n \n");

	return Ok;
}

int timer_test_int(unsigned long time) {

	int ipc_status, r, irq_set;
	message msg;
	irq_set = timer_subscribe_int();

	while (counter < time * 60) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					timer_int_handler();
					if (counter % 60 == 0) {
						printf("\n Seconds passed: %d ", counter / 60);
					}
				}
				break;
			default:
				break;
			}
		} else {
		}
	}

	timer_unsubscribe_int();

	return Ok;
}

int timer_test_config(unsigned char timer) {

	unsigned char st;

	if (timer_get_conf(timer, &st) != 0) {
		return 1;
	}

	if (timer_display_conf(st) != 0) {
			return 1;
		}


	return Ok;
}

int timer_set_frequency(unsigned char timer, unsigned long freq) {

	unsigned long timerfreqdiv;
	unsigned char timerconfig = 0, newtimerconfig=0;
	unsigned char lsb, msb;

	if (freq <=0) {
			printf("error: frequency can't be zero or under");
		}

	if (freq > TIMER_FREQ) {
		printf("error: frequency bigger than TIMER_FREQ");
	}

	timerfreqdiv = TIMER_FREQ / freq; //timerfreqdiv is what we send to alter the i8254 timer frequency
	lsb = timerfreqdiv & 0xFF;
	msb = (timerfreqdiv >> 8) & 0xFF;
	timer_get_conf(0, &timerconfig);
	newtimerconfig = timerconfig & (BIT(0)| BIT(1)|BIT(2)|BIT(3));
	newtimerconfig =newtimerconfig | TIMER_LSB_MSB;
	newtimerconfig = newtimerconfig | TIMER_SEL0;
	sys_outb(TIMER_CTRL, newtimerconfig);
	sys_outb(TIMER_0, lsb);
	sys_outb(TIMER_0, msb);

	return Ok;
}

int timer_test_time_base(unsigned long freq) { //calls timer_set_frequency
	timer_set_frequency(0, freq); //changes timer 0 frequency

	return Ok;
}
