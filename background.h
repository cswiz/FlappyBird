#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "object.h"
#include "physics.h"

typedef struct Background Background;

struct Background {
	Object interface;

	Position position;
	Velocity velocity;
	Acceleration acceleration;

	SDL_Rect sprite;
};

Background *createBackground(void);

#endif
