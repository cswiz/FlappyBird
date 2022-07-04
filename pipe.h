#ifndef PIPE_H
#define PIPE_H

#include "object.h"
#include "physics.h"

typedef enum {
	TOP,
	BOTTOM,
} PipeType;

typedef struct Pipe Pipe;
typedef struct PipePair PipePair;
typedef struct PipeGroup PipeGroup;

struct Pipe {
	Object interface;

	Position position;
	Velocity velocity;
	Acceleration acceleration;

	SDL_Rect sprite;
};

struct PipePair {
	Object interface;

	Pipe *top;
	Pipe *bottom;

	double distance;

	PipePair *next;
};

struct PipeGroup {
	Object interface;

	PipePair *head;
	PipePair *tail;

	double distance;
};

PipeGroup *createPipeGroup(void);

#endif
