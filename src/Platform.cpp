#include "Platform.h"
#include "game.h"

Platform::Platform()
	: Crosser(){ }

Platform::Platform(std::istream& entrada, Game* g, std::string name)
	: Crosser(entrada, g, name){ }

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
