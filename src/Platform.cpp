#include "Platform.h"
#include "PlayState.h"

Platform::Platform(std::istream& entrada, PlayState* g, std::string name)
	: Crosser(entrada, g, name){ }

PlayState::Collision Platform::checkCollision(const SDL_FRect& frog)
{
	PlayState::Collision collision;
	collision.type = PlayState::NONE;
	SDL_FRect rect = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&frog, &rect)) {
		collision.type = PlayState::PLATFORM;
		collision.speed = speed;
	}
	return collision;

}
