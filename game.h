#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "video.h"
#include "background.h"
#include "pipe.h"
#include "score.h"
#include "bird.h"

typedef enum {
	INGAME,
	GAMEOVER,
} State;

typedef struct Game Game;

struct Game {
	int (*run)(Game *self);

	State state;
	SDL_Event event;

	Video *video;

	Background *background;
	PipeGroup *pipeGroup;
	Score *score;
	Bird *bird;

	PipePair *pipePairToPass;
};

Game *createGame(void);

#endif
