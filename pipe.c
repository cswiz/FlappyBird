#include "pipe.h"

static void updatePipe(void *self)
{
	((Pipe *)self)->position.x += ((Pipe *)self)->velocity.x;
	((Pipe *)self)->position.y += ((Pipe *)self)->velocity.y;

	((Pipe *)self)->velocity.x += ((Pipe *)self)->acceleration.x;
	((Pipe *)self)->velocity.y += ((Pipe *)self)->acceleration.y;
}

static void renderPipe(void *self, Video *video)
{
	SDL_Rect dstrect = ((Pipe *)self)->sprite;
	dstrect.x = ((Pipe *)self)->position.x;
	dstrect.y = ((Pipe *)self)->position.y;

	SDL_RenderCopy(video->renderer, video->spriteSheetTexture,
		       &((Pipe *)self)->sprite, &dstrect);
}

static Pipe *createPipe(PipeType pipeType, Position position)
{
	Pipe *pipe = malloc(sizeof(Pipe));

	((Object *)pipe)->update = updatePipe;
	((Object *)pipe)->render = renderPipe;
	((Object *)pipe)->free = free;

	pipe->position = position;
	pipe->velocity = (Velocity){ .x = -1, .y = 0 };
	pipe->acceleration = (Acceleration){ .x = 0, .y = 0 };

	switch (pipeType) {
	case TOP:
		pipe->sprite =
			(SDL_Rect){ .x = 112, .y = 646, .w = 52, .h = 320 };
		break;

	case BOTTOM:
		pipe->sprite =
			(SDL_Rect){ .x = 168, .y = 646, .w = 52, .h = 320 };
		break;

	default:
		pipe->sprite = (SDL_Rect){ .x = 0, .y = 0, .w = 0, .h = 0 };
		break;
	}

	return pipe;
}

static void updatePipePair(void *self)
{
	Pipe *topPipe = ((PipePair *)self)->top;
	((Object *)topPipe)->update(topPipe);

	Pipe *bottomPipe = ((PipePair *)self)->bottom;
	((Object *)bottomPipe)->update(bottomPipe);
}

static void renderPipePair(void *self, Video *video)
{
	Pipe *topPipe = ((PipePair *)self)->top;
	((Object *)topPipe)->render(topPipe, video);

	Pipe *bottomPipe = ((PipePair *)self)->bottom;
	((Object *)bottomPipe)->render(bottomPipe, video);
}

static void freePipePair(void *self)
{
	Pipe *topPipe = ((PipePair *)self)->top;
	((Object *)topPipe)->free(topPipe);

	Pipe *bottomPipe = ((PipePair *)self)->bottom;
	((Object *)bottomPipe)->free(bottomPipe);

	free(self);
}

static PipePair *createPipePair(Position center)
{
	PipePair *pipePair = malloc(sizeof(PipePair));

	((Object *)pipePair)->update = updatePipePair;
	((Object *)pipePair)->render = renderPipePair;
	((Object *)pipePair)->free = freePipePair;

	pipePair->distance = 150;

	Position position = { .x = 0, .y = 0 };

	position = (Position){ .x = center.x - 26,
			       .y = center.y - pipePair->distance / 2 - 322 };
	pipePair->top = createPipe(TOP, position);

	position = (Position){ .x = center.x - 26,
			       .y = center.y + pipePair->distance / 2 };
	pipePair->bottom = createPipe(BOTTOM, position);

	pipePair->next = NULL;

	return pipePair;
}

static int getRandomInteger(int start, int end)
{
	return rand() % (end - start) + start;
}

static void updatePipeGroup(void *self)
{
	PipePair *pipePair = ((PipeGroup *)self)->head;

	PipePair *tailPipePair = ((PipeGroup *)self)->tail;
	Pipe *headTopPipe = pipePair->top;
	Pipe *tailTopPipe = tailPipePair->top;

	if (headTopPipe->position.x + 52 < 0) {
		printf("got here!\n");
		((PipeGroup *)self)->head = ((PipeGroup *)self)->head->next;
		((Object *)pipePair)->free(pipePair);
		Position center = { .x = tailTopPipe->position.x +
					 ((PipeGroup *)self)->distance,
				    .y = 256 + getRandomInteger(-100, 100) };
		pipePair = createPipePair(center);
		((PipeGroup *)self)->tail->next = pipePair;
		((PipeGroup *)self)->tail = pipePair;
	}

	while (pipePair) {
		((Object *)pipePair)->update(pipePair);
		pipePair = pipePair->next;
	}
}

static void renderPipeGroup(void *self, Video *video)
{
	PipePair *pipePair = ((PipeGroup *)self)->head;

	while (pipePair) {
		((Object *)pipePair)->render(pipePair, video);
		pipePair = pipePair->next;
	}
}

static void freePipeGroup(void *self)
{
	PipePair *pipePair = ((PipeGroup *)self)->head;

	while (pipePair) {
		((Object *)pipePair)->free(pipePair);
		pipePair = pipePair->next;
	}

	free(self);
}

PipeGroup *createPipeGroup(void)
{
	PipeGroup *pipeGroup = malloc(sizeof(PipeGroup));

	((Object *)pipeGroup)->update = updatePipeGroup;
	((Object *)pipeGroup)->render = renderPipeGroup;
	((Object *)pipeGroup)->free = freePipeGroup;

	/* Position center = { .x = 400, .y = 256 + getRandomInteger(-100, 100) }; */
	/* PipePair *pipePair = createPipePair(center); */
	/* pipeGroup->head = pipePair; */
	/* pipeGroup->tail = pipePair; */

	pipeGroup->head = NULL;
	pipeGroup->tail = NULL;

	pipeGroup->distance = 200;

	for (int i = 0; i < 2; i++) {
		Position center = { .x = 400 + pipeGroup->distance * i,
				    .y = 256 + getRandomInteger(-100, 100) };
		PipePair *pipePair = createPipePair(center);

		if (!pipeGroup->head) {
			pipeGroup->head = pipePair;
			pipeGroup->tail = pipePair;
			continue;
		}

		pipeGroup->tail->next = pipePair;
		pipeGroup->tail = pipePair;
	}

	return pipeGroup;
}
