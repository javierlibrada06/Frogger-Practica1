#include "Vehicle.h"
#include "vector2D.h"
#include "PlayState.h"
#include "texture.h"
#include "FileFormatError.h"
#include "Crosser.h"
#include <string>
#include <iostream>
using namespace std;

Vehicle::Vehicle(istream& entrada, PlayState* g, std::string name)
	: Crosser(entrada, g, name)
{
	int type;
	if (!(entrada >> type)) throw FileFormatError(name, g->getArchiveLine(), "Error de lectura sobre el tipo de coche");
	texture = game->getGame()->getTexture(SDLApplication::TextureName(SDLApplication::CAR1 + (type - 1)));
	backJump = 0;
}

Vehicle::~Vehicle()
{
	texture = nullptr;
	game = nullptr;
}

PlayState::Collision Vehicle::checkCollision(const SDL_FRect& frog)
{
	PlayState::Collision collision;
	collision.type = PlayState::NONE;
	SDL_FRect rect = getBoundingBox();

	if (SDL_HasRectIntersectionFloat(&frog, &rect)) {
		collision.type = PlayState::ENEMY;
		collision.speed = speed;
	}
	return collision;
}
