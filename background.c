#include "background.h"

static void update(void *self)
{
	((Background *)self)->position.x += ((Background *)self)->velocity.x;
	((Background *)self)->position.y += ((Background *)self)->velocity.y;

	((Background *)self)->velocity.x +=
		((Background *)self)->acceleration.x;
	((Background *)self)->velocity.y +=
		((Background *)self)->acceleration.y;
}

static void render(void *self, Video *video)
{
	SDL_Rect dstrect = ((Background *)self)->sprite;
	dstrect.x = ((Background *)self)->position.x;
	dstrect.y = ((Background *)self)->position.y;

	SDL_RenderCopy(video->renderer, video->spriteSheetTexture,
		       &((Background *)self)->sprite, &dstrect);
}

Background *createBackground(void)
{
	Background *background = malloc(sizeof(Background));

	((Object *)background)->update = update;
	((Object *)background)->render = render;
	((Object *)background)->free = free;

	background->position = (Position){ .x = 0, .y = 0 };
	background->velocity = (Velocity){ .x = 0, .y = 0 };
	background->acceleration = (Acceleration){ .x = 0, .y = 0 };
	background->sprite = (SDL_Rect){ .x = 0, .y = 0, .w = 288, .h = 512 };

	return background;
}
