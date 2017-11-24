#include <unistd.h>
#include <stdlib.h>
#include "defs.h"
#include "video_gr.h"
#include "kbd.h"



/*
 * TO DO: APAGAR
 */
#define VRAM_PHYS_ADDR	0xE0000000
#define H_RES             1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8



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
				setColorPixel(i+H_RES/2-size/2, j+V_RES/2-size/2, color, ptr);
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
		//putPixel(xi, yi, color);

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
	
	/* To be completed */
	return 1;
	
}	

int test_move(char *xpm[], unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, short s, unsigned short f) {

	/* To be completed */
	return 1;
	
}	

int test_controller() {

	/* To be completed */
	return 1;
	
}	
	
