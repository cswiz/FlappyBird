#include "bird.h"

static void update(void *self)
{
	((Bird *)self)->position.x += ((Bird *)self)->velocity.x;
	((Bird *)self)->position.y += ((Bird *)self)->velocity.y;

	((Bird *)self)->velocity.x += ((Bird *)self)->acceleration.x;
	((Bird *)self)->velocity.y += ((Bird *)self)->acceleration.y;

	((Bird *)self)->angle += ((Bird *)self)->angularVelocity;
	if (((Bird *)self)->angle > 85) {
		((Bird *)self)->angle = 85;
	}
}

static void render(void *self, Video *video)
{
	SDL_Rect srcrect = ((Bird *)self)->sprite[1];
	int frameElapsed = video->frame - ((Bird *)self)->lastFlapFrame;
	if (frameElapsed > 0 && frameElapsed <= 5) {
		srcrect = ((Bird *)self)->sprite[0];
	} else if (frameElapsed > 5 && frameElapsed <= 10) {
		srcrect = ((Bird *)self)->sprite[1];
	} else if (frameElapsed > 10 && frameElapsed <= 15) {
		srcrect = ((Bird *)self)->sprite[2];
	}

	SDL_Rect dstrect = ((Bird *)self)->sprite[1];
	dstrect.x = ((Bird *)self)->position.x;
	dstrect.y = ((Bird *)self)->position.y;

	SDL_RenderCopyEx(video->renderer, video->spriteSheetTexture, &srcrect,
			 &dstrect, ((Bird *)self)->angle, NULL, SDL_FLIP_NONE);
}

static void flap(Bird *self, Video *video)
{
	self->velocity = self->flapVelocity;
	self->angle = self->flapAngle;
	self->lastFlapFrame = video->frame;
}

Bird *createBird(void)
{
	Bird *bird = malloc(sizeof(Bird));

	((Object *)bird)->update = update;
	((Object *)bird)->render = render;
	((Object *)bird)->free = free;

	bird->flap = flap;
	bird->flapVelocity = (Velocity){ .x = 0, .y = -5 };
	bird->flapAngle = -45;
	bird->lastFlapFrame = 0;

	bird->position = (Position){ .x = 50, .y = 200 };
	bird->velocity = (Velocity){ .x = 0, .y = -5 };
	bird->acceleration = (Acceleration){ .x = 0, .y = 0.32 };

	bird->angle = -45;
	bird->angularVelocity = 2.0;

	bird->sprite[0] = (SDL_Rect){ .x = 6, .y = 982, .w = 34, .h = 24 };
	bird->sprite[1] = (SDL_Rect){ .x = 62, .y = 982, .w = 34, .h = 24 };
	bird->sprite[2] = (SDL_Rect){ .x = 118, .y = 982, .w = 34, .h = 24 };

	return bird;
}
