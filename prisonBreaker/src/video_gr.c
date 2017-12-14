#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "vbe.h"
#include "read_xpm.h"
#include "defs.h"

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"

#define VRAM_PHYS_ADDR	0xE0000000
#define H_RES             1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8
 */

/* Private global variables */

static short *video_mem;		/* Process (virtual) address to which VRAM is mapped */
static short *mBuffer;
static short *buffer;


static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

int vg_exit() {
  struct reg86u reg86;

  reg86.u.b.intno = 0x10; /* BIOS video services */

  reg86.u.b.ah = 0x00;    /* Set Video Mode function */
  reg86.u.b.al = 0x03;    /* 80x25 text mode*/

  if( sys_int86(&reg86) != OK ) {
      printf("\tvg_exit(): sys_int86() failed \n");
      return 1;
  } else
      return 0;
}


void *vg_init(unsigned short mode){

	struct reg86u reg86;
	vbe_mode_info_t vmi_p;

	reg86.u.b.ah = VBE_CALL; // VBE call,
	reg86.u.b.al = SET_VBE_MODE; //function 02 -- set VBE mode
	reg86.u.w.bx = SET_LINEAR_FRAME_BUFFER | mode; // set bit 14| mode
	reg86.u.b.intno = VIDEO_CARD_INTERRUPT;

	if (sys_int86(&reg86) != OK) {
		printf("set_vbe_mode: sys_int86() failed \n");
		return NULL;
	}

	if (vbe_get_mode_info(mode, &vmi_p) != OK) {
			//TODO printf
			return NULL;
	}

	h_res =vmi_p.XResolution;
	v_res =vmi_p.YResolution;
	bits_per_pixel = vmi_p.BitsPerPixel;

	int r;
	struct mem_range mr;
	unsigned int vram_base =  vmi_p.PhysBasePtr; /* VRAM's physical addresss */
	unsigned int vram_size = h_res * v_res * bits_per_pixel/8; /* VRAM's size, but you can use the frame-buffer size, instead */


	/* Allow memory mapping */

	mr.mr_base = (phys_bytes) vram_base;
	mr.mr_limit = mr.mr_base + vram_size;

	if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		panic("sys_privctl (ADD_MEM) failed: %d\n", r);

	/* Map memory */

	video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);
	mBuffer = (short*) malloc(h_res * v_res *bits_per_pixel/8);
	buffer = (short*) malloc(h_res * v_res *bits_per_pixel/8);


	if (video_mem == MAP_FAILED)
		panic("couldn't map video memory");

	return video_mem;


}



void flipMBuffer() {
	memcpy(mBuffer, buffer, h_res * v_res *bits_per_pixel/8);

}


void flipDisplay(){
	memcpy(video_mem, mBuffer, h_res * v_res *bits_per_pixel/8);

}

short getHorResolution(){
	return h_res;
}

short getVerResolution(){
	return v_res;
}

char* getGraphicsBuffer(){
	return (char *) buffer;
}

void setColorPixel(int x, int y, short color, short * ptr){
	*(ptr + y * h_res + x) = color;
	int offset =  (y * h_res) + x;

	printf("x: %d, y: %d, offset: %d, pos: %p\n", x, y, offset, ptr + offset);

}

int validCoord(int x, int y){
	if(x<h_res && y<v_res)
		return 1;
	else return 0;


}

/*
int print_sprite(char *xpm[], unsigned short xi, unsigned short yi, short * ptr) {

	int wd, hg, i, j;
	char *sprite = read_xpm(xpm, &wd, &hg);

	for (i = 0; i < wd; i++) {
		for (j = 0; j < hg; j++)
			if (validCoord(i + xi, j + yi))
				setColorPixel(i + xi, j + yi, *(sprite + j * wd + i), ptr);

	}

	return 0;
}
*/



int draw_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {

	int i, j;
	for (j = y; j < size + y; j++) {
		for (i = x; i < size + x; i++) {
			if (validCoord(i + h_res / 2 - size / 2, j + v_res / 2 - size / 2))
				setColorPixel(i + h_res / 2 - size / 2, j + v_res / 2 - size / 2,
						color, buffer);
		}
	}

	return 0;

}

