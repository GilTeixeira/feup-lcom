#include <minix/syslib.h>
#include <minix/drivers.h>

#include "i8254.h"


int timer_subscribe_int(void ) {

	return 1;
}

int timer_unsubscribe_int() {

	return 1;
}

void timer_int_handler() {

}

int timer_get_conf(unsigned char timer, unsigned char *st) {
	unsigned long stout;
	port_t timerport;
	unsigned long timerselect;

	switch (timer) {
	case 0: //timer 0
		timerport = TIMER_0;
		timerselect = TIMER_SEL0;
		break;
	case 1: //timer1
		timerport = TIMER_1;
		timerselect = TIMER_SEL1;
		break;
	case 2: //timer2
		timerport = TIMER_2;
		timerselect = TIMER_SEL2;
		break;

	default:
		printf("error: timer doesn't exist");
		return 1;
	}
	stout = TIMER_RB_CMD | timerselect | TIMER_RB_STATUS_;
	sys_outb(TIMER_CTRL, stout);
	sys_inb(timerport,(unsigned long int *) st );
	return 0;
}

int timer_display_conf(unsigned char conf) {
	printf("type of access: ");
	if (conf & (BIT(5) | BIT(4)) == BIT(5) | BIT(4))
		printf("LSB followed by MSB \n");
	else if (conf & (BIT(5)) == BIT(5))
		printf("MSB \n");
	else if (conf & (BIT(4)) == BIT(4))
		printf("LSB \n");

	printf("Operating mode: ");
	if (conf & BIT(3) == 0) {
		if (conf & BIT(2) == 0)
			if (conf & BIT(1) == 0)
				printf(" Operating mode 0 \n");
			else
				printf("Operating mode 1 \n");
		else if (conf & BIT(1) == 0)
			printf("Operating mode 2 \n");
		else
			printf("Operating mode 3 \n");
	} else {
		if (conf & BIT(2) == 0) {
			if (conf & BIT(1) == 0)
				printf(" Operating mode 4 \n");
			else
				printf("Operating mode 5 \n");
		} else {
			if (conf & BIT(1) == 0)
				printf("Operating mode 2 \n");
			else
				printf("Operating mode 3 \n");
		}
	}

	printf("Counting mode: ");
	if (conf & BIT(0) == 0)
					printf("Binary \n");
				else
					printf("BCD \n");

	return 0;
}

int timer_test_int(unsigned long time) {

	return 1;
}

int timer_test_config(unsigned char timer) {
	unsigned char st;

	// testar as duas funções e avisar no caso de dar erro
	if(timer_get_conf(timer,&st)!=0){
	//se não der avisar o erro
		return 1;
	} else
	{
	//se der, testar o outro
	if(timer_display_conf(timer)!=0){
	return 1;
	}}


	return 0;
}


int timer_set_frequency(unsigned char timer, unsigned long freq) {

	unsigned char timerconfig;
	char lsb,msb;
	//Changes the operating frequency of a timer.
	//Must not change the 3 LSBs (mode and BCD/binary) of the timer's control word.
	if (timer != 0 && timer != 1 && timer != 2) {
		printf("error: impossible timer");
	}

	if (freq > TIMER_FREQ) {
		printf("error: frequency bigger than TIMER_FREQ");
	}

	long timerfreqdiv = TIMER_FREQ / freq;
	lsb= freq;
	msb= freq>>8;

	timer_get_conf(0, &timerconfig);
	timerconfig= timerconfig | TIMER_LSB_MSB;
	sys_outb(TIMER_CTRL, timerconfig);
	sys_outb(TIMER_0, lsb);
	sys_outb(TIMER_0, msb);


	return 0;
}

int timer_test_time_base(unsigned long freq) {

timer_set_frequency(0,freq);


//enviar para 0x40 a informação com o timer que eu quero (timer 0, timer 1 , etc)

//vector 0x08


	return 0;
}
