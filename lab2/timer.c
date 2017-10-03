#include <minix/syslib.h>
#include <minix/drivers.h>

int timer_set_frequency(unsigned char timer, unsigned long freq) {

	return 1;
}

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
	case '0': //timer 0
		timerport = TIMER_0;
		timerselect = TIMER_SEL0;
		break;
	case '1': //timer1
		timerport = TIMER_1;
		timerselect = TIMER_SEL0;
		break;
	case '2': //timer2
		timerport = TIMER_2;
		timerselect = TIMER_SEL0;
		break;
	}

	stout = TIMER_RB_CMD | timerselect | TIMER_RB_STATUS_;
	sys_outb(TIMER_CTRL, stout);
	sys_inb(timerport, &st);
	return 0;
}

int timer_display_conf(unsigned char conf) {

	//develop


	return 1;
}

int timer_test_int(unsigned long time) {

	return 1;
}

int timer_test_config(unsigned char timer) {
	// testar as duas funções e avisar no caso de dar erro
	if(timer_get_conf()!=0){
	//se não der avisar o erro
		return 1;
	} else
	{
	//se der, testar o outro
	if(timer_display_conf()!=0){
	return 1;
	}}


	return 0;
}

int timer_test_time_base(unsigned long freq) {
	unsigned long cenasoutbin,cenasoutbcd;
cenasoutbin=cenasoutbin|BIT(2)|BIT(3)|BIT(6);

timer_set_frequency();
//cenasoutbin=00100110;
    //cenasoutbcd=00100111;
//USAR O timerfreq


//enviar para 0x40 a informação com o timer que eu quero (timer 0, timer 1 , etc)

//vector 0x08


	return 1;
}
