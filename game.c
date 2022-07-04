#include "game.h"

static void quit(Game *self)
{
	self->video->free(self->video);

	((Object *)self->background)->free(self->background);
	((Object *)self->pipeGroup)->free(self->pipeGroup);
	((Object *)self->score)->free(self->score);
	((Object *)self->bird)->free(self->bird);

	SDL_Quit();
	free(self);

	exit(EXIT_SUCCESS);
}

static void processEachEvent(Game *self)
{
	switch (self->event.type) {
	case SDL_KEYDOWN:
	case SDL_MOUSEBUTTONDOWN:
	case SDL_FINGERDOWN:
		switch (self->state) {
		case INGAME:
			printf("inputdown frame: %d\n", self->video->frame);
			self->bird->flap(self->bird, self->video);
			break;

		case GAMEOVER:
			((Object *)self->bird)->free(self->bird);
			((Object *)self->pipeGroup)->free(self->pipeGroup);
			self->bird = createBird();
			self->bird->flap(self->bird, self->video);
			self->pipeGroup = createPipeGroup();
			self->pipePairToPass = self->pipeGroup->head;
			self->score->reset(self->score);
			self->state = INGAME;
			break;

		default:
			break;
		}
		break;

	case SDL_QUIT:
		quit(self);
		break;

	default:
		break;
	}
}

static void handleAllEvents(Game *self)
{
	while (SDL_PollEvent(&self->event)) {
		processEachEvent(self);
	}
}

static void update(Game *self)
{
	((Object *)self->background)->update(self->background);
	((Object *)self->pipeGroup)->update(self->pipeGroup);
	((Object *)self->score)->update(self->score);
	((Object *)self->bird)->update(self->bird);
}

static void render(Game *self)
{
	SDL_RenderClear(self->video->renderer);

	((Object *)self->background)->render(self->background, self->video);
	((Object *)self->pipeGroup)->render(self->pipeGroup, self->video);
	((Object *)self->score)->render(self->score, self->video);
	((Object *)self->bird)->render(self->bird, self->video);

	SDL_RenderPresent(self->video->renderer);
}

static bool hasPassed(Bird *bird, PipePair *pipePair)
{
	return bird->position.x >= pipePair->top->position.x;
}

static bool detectCollision(Game *self)
{
	const int SCREEN_HEIGHT = 512;
	if (self->bird->position.y < 0 ||
	    self->bird->position.y + self->bird->sprite[0].h > SCREEN_HEIGHT) {
		return true;
	}

	SDL_Rect birdRect = { .x = self->bird->position.x,
			      .y = self->bird->position.y,
			      .w = self->bird->sprite[0].w,
			      .h = self->bird->sprite[0].h };

	PipePair *pipePair = self->pipeGroup->head;

	while (pipePair) {
		Pipe *topPipe = pipePair->top;
		SDL_Rect topPipeRect = { .x = topPipe->position.x,
					 .y = topPipe->position.y,
					 .w = topPipe->sprite.w,
					 .h = topPipe->sprite.h };
		if (SDL_HasIntersection(&birdRect, &topPipeRect)) {
			return true;
		}

		Pipe *bottomPipe = pipePair->bottom;
		SDL_Rect bottomPipeRect = { .x = bottomPipe->position.x,
					    .y = bottomPipe->position.y,
					    .w = bottomPipe->sprite.w,
					    .h = bottomPipe->sprite.h };
		if (SDL_HasIntersection(&birdRect, &bottomPipeRect)) {
			return true;
		}

		pipePair = pipePair->next;
	}

	return false;
}

static void capFrameRate(Uint64 tickElapsed)
{
	const int FRAME_PER_SECOND = 60;
	const int TICK_PER_SECOND = 1000;
	const int TICK_PER_FRAME = TICK_PER_SECOND / FRAME_PER_SECOND;

	int64_t tickToDelay = TICK_PER_FRAME - tickElapsed;
	if (tickToDelay > 0) {
		SDL_Delay(tickToDelay);
	}
}

static int run(Game *self)
{
	while (1) {
		Uint64 frameStartTick = SDL_GetTicks64();

		handleAllEvents(self);
		update(self);
		render(self);

		if (hasPassed(self->bird, self->pipePairToPass)) {
			self->score->newScore++;
			self->pipePairToPass = self->pipePairToPass->next;
		}

		if (detectCollision(self)) {
			printf("Collision Detected!\n");
			self->bird->velocity = (Velocity){ .x = 0, .y = 0 };
			self->bird->acceleration =
				(Acceleration){ .x = 0, .y = 0 };
			self->bird->angularVelocity = 0;

			PipePair *pipePair = self->pipeGroup->head;

			while (pipePair) {
				Pipe *topPipe = pipePair->top;
				topPipe->velocity =
					(Velocity){ .x = 0, .y = 0 };
				topPipe->acceleration =
					(Acceleration){ .x = 0, .y = 0 };

				Pipe *bottomPipe = pipePair->bottom;
				bottomPipe->velocity =
					(Velocity){ .x = 0, .y = 0 };
				bottomPipe->acceleration =
					(Acceleration){ .x = 0, .y = 0 };

				pipePair = pipePair->next;
			}

			self->state = GAMEOVER;
		}

		Uint64 frameEndTick = SDL_GetTicks64();
		Uint64 tickElapsed = frameEndTick - frameStartTick;
		printf("Tick Elapsed: %lld\n", tickElapsed);

		capFrameRate(tickElapsed);

		self->video->frame++;
		printf("frame: %d\n", self->video->frame);
	}

	return EXIT_FAILURE;
}

Game *createGame(void)
{
	Game *game = malloc(sizeof(Game));

	game->run = run;

	game->state = INGAME;

	game->video = createVideo();

	game->background = createBackground();
	game->pipeGroup = createPipeGroup();
	game->score = createScore();
	game->bird = createBird();

	game->pipePairToPass = game->pipeGroup->head;

	return game;
}
