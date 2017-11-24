#include <minix/syslib.h>
#include <minix/driver.h>
#include <unistd.h>
#include <stdlib.h>
#include "defs.h"
#include "video_gr.h"
#include "read_xpm.h"
#include "kbd.h"
#include "timer.h"
#include "i8042.h"
#include "i8254.h"





void *video_test_init(unsigned short mode, unsigned short delay) {

	void * ret = vg_init(mode);
	sleep(delay);
	vg_exit();


	return ret;
	
}


int video_test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {
	
	int i, j;
	char * ptr = vg_init(DEFAULT_MODE);

	for (i = x; i < size + x; i++) {
			for (j = y; j < size + y; j++) {
				setColorPixel(i+HRES/2-size/2, j+VRES/2-size/2, color, ptr);
			}
		}

	waitForEscRelease();

	vg_exit();

	return 0;

}

int video_test_line(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, unsigned long color) {

	char * ptr = vg_init(DEFAULT_MODE);

	int d;
	int dx, dy;
	int Eincr, NEincr;
	int yincr;
	int t;

	dx = abs(xf - xi);
	dy = abs(yf - yi);
	if (dy <= dx) {
		if (xf < xi) {
			t = xf;
			xf = xi;
			xi = t;
			t = yf;
			yf = yi;
			yi = t;
		}
		if (yf > yi)
			yincr = 1;
		else
			yincr = -1;
		d = 2 * dy - dx;
		Eincr = 2 * dy;
		NEincr = 2 * (dy - dx);
		setColorPixel(xi, yi, color, ptr);

		for (xi++; xi <= xf; xi++) {
			if (d < 0)
				d += Eincr;
			else {
				d += NEincr;
				yi += yincr;
			}
//
			setColorPixel(xi, yi, color, ptr);
		}
	} else {

		if (yf < yi) {
			t = xf;
			xf = xi;
			xi = t;
			t = yf;
			yf = yi;
			yi = t;
		}
		if (xf > xi)
			yincr = 1;
		else
			yincr = -1;
		d = 2 * dx - dy;
		Eincr = 2 * dx;
		NEincr = 2 * (dx - dy);
		setColorPixel(xi, yi, color, ptr);

		for (yi++; yi <= yf; yi++) {
			if (d < 0)
				d += Eincr;
			else {
				d += NEincr;
				xi += yincr;
			}
			setColorPixel(xi, yi, color, ptr);
		}
	}

	waitForEscRelease();

	vg_exit();

	return 0;

}
	
int test_xpm(char *xpm[], unsigned short xi, unsigned short yi) {
	int wd, hg, i, j;
	char *sprite = read_xpm(xpm, &wd, &hg);

	char * ptr = vg_init(DEFAULT_MODE);

	for (i = 0; i < wd; i++) {
				for (j = 0; j < hg; j++) {
					setColorPixel(i+xi, j+yi, *(sprite + j * wd + i) , ptr);
				}
			}

	
	waitForEscRelease();

	vg_exit();

	return 0;

	
}	

int test_move(char *xpm[], unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, short s, unsigned short f) {


	int ipc_status, r, irq_set_timer, irq_set_kbd;
	int counter = 0;
	int i, j;
	unsigned long code = 0;
	unsigned long stat;

	unsigned short xInc;
	unsigned short yInc;

	if (yf - yi != 0)
		yInc = 1;
	else
		yInc = 0;

	if (xf - xi != 0)
		xInc = 1;
	else
		xInc = 0;


	//printf("xInc= %d\n", xInc);
	//printf("yInc= %d\n", yInc);

	//waitForEscRelease();

	message msg;

	irq_set_kbd = kbd_subscribe_int();
	if (irq_set_kbd < 0)
		return KBD_SUB_ERROR;

	irq_set_timer = timer_subscribe_int();
	if (irq_set_timer < 0)
		return TIMER_SUB_ERROR;

	int wd, hg;
	char *sprite = read_xpm(xpm, &wd, &hg);

	char * ptr = vg_init(DEFAULT_MODE);

	while (code != ESC) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_kbd) { /* subscribed interrupt */

					kbd_handler();
					code = globalCode;

				}
				if (msg.NOTIFY_ARG & irq_set_timer) { /* subscribed interrupt */
					int xIncrement = s*counter*xInc;
					int yIncrement = s*counter*yInc;



					for (i = 0; i < wd; i++) {
								for (j = 0; j < hg; j++) {
									setColorPixel(i+xi+xIncrement, j+yi+yIncrement, *(sprite + j * wd + i) , ptr);
								}
							}

					counter++;
				}
				break;

			default:
				break;
			}
		} else {
		}
	}

	if (sys_inb(STAT_REG, &stat) != Ok)
		return SYS_IN_ERROR;

	if (stat & OBF) {
		if (sys_inb(OUT_BUF, &code) != Ok)
			return SYS_IN_ERROR;
	}

	if (timer_unsubscribe_int() != Ok)
		return TIMER_UNSUB_ERROR;

	if (kbd_unsubscribe_int() != Ok)
		return KBD_UNSUB_ERROR;

	vg_exit();

	return Ok;
	
}	

int test_controller() {

	/* To be completed */
	return 1;
	
}	
	
