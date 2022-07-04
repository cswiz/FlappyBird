#ifndef SCORE_H
#define SCORE_H

#include "object.h"
#include "physics.h"

typedef struct Digit Digit;
typedef struct Score Score;

struct Digit {
	Object interface;

	SDL_Rect sprite;

	Position position;

	Digit *next;
};

struct Score {
	Object interface;

	void (*reset)(Score *self);

	Digit *head;
	Digit *tail;
	int digitSpace;

	int oldScore;
	int newScore;
};

Score *createScore(void);

#endif
