#include <stdio.h>
#include "defs.h"
#include "i8042.h"
#include "i8254.h"
#include "video_gr.h"
#include "prisonBreaker.h"

#include "test5.h"

int main(int argc, char **argv) {

	vg_init(DEFAULT_MODE);

	PrisonBreaker* flappy = (PrisonBreaker*) initPrisonBreaker();
	while (!flappy->done) {
		updatePrisonBreaker(flappy);

		if (!flappy->done) {
			if (flappy->draw)
				drawPrisonBreaker(flappy);

			flipMBuffer();
			flipDisplay();
		}
	}
	stopPrisonBreaker(flappy);

	vg_exit();

	return Ok;
}
