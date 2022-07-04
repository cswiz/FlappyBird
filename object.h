#ifndef OBJECT_H
#define OBJECT_H

#include "video.h"

typedef struct Object Object;

struct Object {
	void (*update)(void *object);
	void (*render)(void *object, Video *video);
	void (*free)(void *object);
};

#endif
