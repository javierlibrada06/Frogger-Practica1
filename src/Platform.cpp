#include "Platform.h"
#include "game.h"

Game::Collision Platform::checkCollision(const SDL_FRect& frog)
{
	Game::Collision collision;
	collision.type = Game::NONE;
	SDL_FRect rect = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&frog, &rect)) {
		collision.type = Game::PLATFORM;
		collision.speed = speed;
	}
	return collision;

}