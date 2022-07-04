#include "game.h"

int main(int argc, char *argv[])
{
	Game *game = createGame();
	return game->run(game);
}
