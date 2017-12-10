#include <stdio.h>
#include "defs.h"
#include "i8042.h"
#include "i8254.h"
#include "video_gr.h"

#include "test5.h"

int main(int argc, char **argv) {

	vg_init(DEFAULT_MODE);

	draw_square(1, 1, 200, 0xFFFFFF);

	waitForEscRelease();

	flipMBuffer();

	waitForEscRelease();

	flipDisplay();

	waitForEscRelease();

	vg_exit();

	return Ok;
}
