#include <minix/syslib.h>
#include <minix/drivers.h>

int timer_set_frequency(unsigned char timer, unsigned long freq) {

	return 1;
}

int timer_subscribe_int(void) {

	return 1;
}

int timer_unsubscribe_int() {

	return 1;
}

void timer_int_handler() {

}

int timer_get_conf(unsigned char timer, unsigned char *st) {

	unsigned long confRead;

	 unsigned long timerStatus;

	 /*
	int timerToRead = atoi(timer);
	int timerAddress;

	switch (timerToRead) {
	case 0:
		timerAddress = TIMER_0;
		break;
	case 1:
		timerAddress = TIMER_1;
		break;
	case 2:
		timerAddress = TIMER_2;
		break;

	}

	if (sys_inb(timerAddress, &confRead) == 0)
		return 0;
	else
		return 1;
		*/
}

int timer_display_conf(unsigned char conf) {

	return 1;
}

int timer_test_time_base(unsigned long freq) {

	return 1;
}

int timer_test_int(unsigned long time) {

	return 1;
}

int timer_test_config(unsigned char timer) {

	return 1;
}
