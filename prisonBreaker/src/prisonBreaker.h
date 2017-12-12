#include "bitmap.h"

typedef struct {
	int IRQ_SET_KBD;
	int IRQ_SET_TIMER;

	Bitmap* fundo;

	int done, draw;
	unsigned long scancode;
} PrisonBreaker;

PrisonBreaker* initPrisonBreaker();
void updatePrisonBreaker(PrisonBreaker* prisonBreaker);
void drawPrisonBreaker(PrisonBreaker* prisonBreaker);
void stopPrisonBreaker(PrisonBreaker* prisonBreaker);
