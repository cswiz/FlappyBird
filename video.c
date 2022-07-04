#include "video.h"

static void initSDLVideo(void)
{
	if (SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL_ERROR: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

static SDL_Window *createWindow(void)
{
	const char *GAME_TITLE = "FlappyBird";
	const int SCREEN_WIDTH = 288;
	const int SCREEN_HEIGHT = 512;

	SDL_Window *gameWindow =
		SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED,
				 SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
				 SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (!gameWindow) {
		printf("SDL_ERROR: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	return gameWindow;
}

static SDL_Renderer *createRendererFromWindow(SDL_Window *window)
{
	SDL_Renderer *renderer = SDL_CreateRenderer(
		window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer) {
		printf("SDL_ERROR: %s\n", SDL_GetError());
		renderer = SDL_CreateRenderer(
			window, -1,
			SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
	}

	if (!renderer) {
		printf("SDL_ERROR: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	return renderer;
}

static SDL_Surface *createSurfaceFromFile(const char *path)
{
	SDL_Surface *surface = SDL_LoadBMP(path);

	if (!surface) {
		printf("SDL_ERROR: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	return surface;
}

static SDL_Texture *createTextureFromSurface(SDL_Renderer *renderer,
					     SDL_Surface *surface)
{
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (!texture) {
		printf("SDL_ERROR: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	return texture;
}

static SDL_Texture *createTextureFromFile(SDL_Renderer *renderer,
					  const char *path)
{
	SDL_Surface *surface = createSurfaceFromFile(path);
	SDL_Texture *texture = createTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	return texture;
}

static void freeVideo(Video *self)
{
	SDL_DestroyTexture(self->spriteSheetTexture);
	SDL_DestroyRenderer(self->renderer);
	SDL_DestroyWindow(self->window);
	free(self);
}

Video *createVideo(void)
{
	Video *video = malloc(sizeof(Video));

	initSDLVideo();
	video->window = createWindow();
	video->renderer = createRendererFromWindow(video->window);

	const char *PATH_TO_SPRITE_SHEET = "./atlas.bmp";
	video->spriteSheetTexture =
		createTextureFromFile(video->renderer, PATH_TO_SPRITE_SHEET);

	video->frame = 0;

	video->free = freeVideo;

	return video;
}
