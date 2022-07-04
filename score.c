#include "score.h"

static void renderDigit(void *self, Video *video)
{
	SDL_Rect dstrect = ((Digit *)self)->sprite;
	dstrect.x = ((Digit *)self)->position.x;
	dstrect.y = ((Digit *)self)->position.y;

	SDL_RenderCopy(video->renderer, video->spriteSheetTexture,
		       &((Digit *)self)->sprite, &dstrect);
}

static Digit *createDigit(int d)
{
	Digit *digit = malloc(sizeof(Digit));

	((Object *)digit)->update = NULL;
	((Object *)digit)->render = renderDigit;
	((Object *)digit)->free = free;

	switch (d) {
	case 0:
		digit->sprite =
			(SDL_Rect){ .x = 992, .y = 120, .w = 24, .h = 36 };
		break;

	case 1:
		digit->sprite =
			(SDL_Rect){ .x = 272, .y = 910, .w = 16, .h = 36 };
		break;

	case 2:
		digit->sprite =
			(SDL_Rect){ .x = 584, .y = 320, .w = 24, .h = 36 };
		break;

	case 3:
		digit->sprite =
			(SDL_Rect){ .x = 612, .y = 320, .w = 24, .h = 36 };
		break;

	case 4:
		digit->sprite =
			(SDL_Rect){ .x = 640, .y = 320, .w = 24, .h = 36 };
		break;

	case 5:
		digit->sprite =
			(SDL_Rect){ .x = 668, .y = 320, .w = 24, .h = 36 };
		break;

	case 6:
		digit->sprite =
			(SDL_Rect){ .x = 584, .y = 368, .w = 24, .h = 36 };
		break;

	case 7:
		digit->sprite =
			(SDL_Rect){ .x = 612, .y = 368, .w = 24, .h = 36 };
		break;

	case 8:
		digit->sprite =
			(SDL_Rect){ .x = 640, .y = 368, .w = 24, .h = 36 };
		break;

	case 9:
		digit->sprite =
			(SDL_Rect){ .x = 668, .y = 368, .w = 24, .h = 36 };
		break;

	default:
		break;
	}

	const int SCREEN_WIDTH = 288;
	digit->position.x = (double)(SCREEN_WIDTH - digit->sprite.w) / 2;
	const int DISTANCE_FROM_CEILING = 20;
	digit->position.y = DISTANCE_FROM_CEILING;

	digit->next = NULL;

	return digit;
}

static void push(Score *self, Digit *digit)
{
	if (!self->head) {
		self->head = digit;
		self->tail = digit;
		return;
	}

	digit->next = self->head;
	self->head = digit;

	Digit *d = self->head;
	double sum = 0;
	int cnt = 0;
	while (d) {
		sum += d->sprite.w;
		cnt += 1;
		d = d->next;
	}
	sum += (cnt - 1) * self->digitSpace;
	double x = (288 - sum) / 2;
	d = self->head;
	while (d) {
		d->position.x = x;
		x += d->sprite.w + self->digitSpace;
		d = d->next;
	}
}

static void updateScore(void *self)
{
	int oldScore = ((Score *)self)->oldScore;
	int newScore = ((Score *)self)->newScore;
	if (oldScore == newScore) {
		return;
	}

	Digit *digit = ((Score *)self)->head;
	while (digit) {
		((Object *)digit)->free(digit);
		digit = digit->next;
	}
	((Score *)self)->head = NULL;
	((Score *)self)->tail = NULL;

	while (1) {
		int quotient = newScore / 10;
		int remainder = newScore % 10;

		push(self, createDigit(remainder));

		newScore = quotient;
		if (!newScore) {
			break;
		}
	}

	((Score *)self)->oldScore = ((Score *)self)->newScore;
}

static void renderScore(void *self, Video *video)
{
	Digit *digit = ((Score *)self)->head;

	while (digit) {
		((Object *)digit)->render(digit, video);
		digit = digit->next;
	}
}

static void freeScore(void *self)
{
	Digit *digit = ((Score *)self)->head;

	while (digit) {
		((Object *)digit)->free(digit);
		digit = digit->next;
	}

	free(self);
}

static void reset(Score *self)
{
	Digit *digit = self->head;

	while (digit) {
		((Object *)digit)->free(digit);
		digit = digit->next;
	}

	self->head = createDigit(0);
	self->tail = self->head;
	self->oldScore = 0;
	self->newScore = 0;
}

Score *createScore(void)
{
	Score *score = malloc(sizeof(Score));

	((Object *)score)->update = updateScore;
	((Object *)score)->render = renderScore;
	((Object *)score)->free = freeScore;

	score->reset = reset;

	score->head = createDigit(0);
	score->tail = score->head;
	score->digitSpace = 2;

	score->oldScore = 0;
	score->newScore = 0;

	return score;
}
