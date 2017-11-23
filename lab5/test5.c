#include <unistd.h>
#include "defs.h"
#include "video_gr.h"



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

	sleep(10);

	vg_exit();


}

int video_test_line(unsigned short xi, unsigned short yi, 
		           unsigned short xf, unsigned short yf, unsigned long color) {
	
	/* To be completed */
	
}
	
int test_xpm(char *xpm[], unsigned short xi, unsigned short yi) {
	
	/* To be completed */
	
}	

int test_move(char *xpm[], unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, short s, unsigned short f) {

	/* To be completed */
	
}	

int test_controller() {

	/* To be completed */
	
}	
	
