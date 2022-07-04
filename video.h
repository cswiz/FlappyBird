#ifndef VIDEO_H
#define VIDEO_H

#include <SDL.h>

typedef struct Video Video;

struct Video {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *spriteSheetTexture;
	int frame;

	void (*free)(Video *self);
};

Video *createVideo(void);

#endif
