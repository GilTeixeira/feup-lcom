
typedef struct {
	int IRQ_SET_KBD;

	int done, draw;
	unsigned long scancode;
} PrisonBreaker;

PrisonBreaker* initPrisonBreaker();
void updatePrisonBreaker(PrisonBreaker* prisonBreaker);
void drawPrisonBreaker(PrisonBreaker* prisonBreaker);
void stopPrisonBreaker(PrisonBreaker* prisonBreaker);
