#include <stdio.h>
#include "defs.h"
#include "i8042.h"
#include "i8254.h"
#include "video_gr.h"
#include "prisonBreaker.h"

#include "test5.h"

int main(int argc, char **argv) {

	vg_init(DEFAULT_MODE);

	PrisonBreaker* prisonBreaker = (PrisonBreaker*) initPrisonBreaker();
	while (!prisonBreaker->done) {
		updatePrisonBreaker(prisonBreaker);

		if (!prisonBreaker->done) {
			if (prisonBreaker->draw)
				drawPrisonBreaker(prisonBreaker);

			flipMBuffer();
			flipDisplay();
		}
	}
	stopPrisonBreaker(prisonBreaker);

	vg_exit();

	return Ok;
}
