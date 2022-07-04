#ifndef BIRD_H
#define BIRD_H

#include <stdbool.h>

#include "object.h"
#include "physics.h"

typedef struct Bird Bird;

struct Bird {
	Object interface;

	void (*flap)(Bird *self, Video *video);
	Velocity flapVelocity;
	Angle flapAngle;
	int lastFlapFrame;

	Position position;
	Velocity velocity;
	Acceleration acceleration;

	Angle angle;
	AngularVelocity angularVelocity;

	SDL_Rect sprite[3];
};

Bird *createBird(void);

#endif
