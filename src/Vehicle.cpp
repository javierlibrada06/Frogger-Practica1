#include "Vehicle.h"
#include "vector2D.h"
#include "PlayState.h"
#include "texture.h"
#include "FileFormatError.h"
#include "Crosser.h"
#include <iostream>
using namespace std;

Vehicle::Vehicle(istream& entrada, PlayState* g, std::string name)
	: Crosser(entrada, g, name)
{
	int type;
	if (!(entrada >> type)) throw FileFormatError(name, g->getArchiveLine(), "Error de lectura sobre el tipo de coche");

	switch (type)
	{
	case 1: texture = game->getGame()->getTexture(SDLApplication::CAR1); break;
	case 2: texture = game->getGame()->getTexture(SDLApplication::CAR2); break;
	case 3: texture = game->getGame()->getTexture(SDLApplication::CAR3); break;
	case 4: texture = game->getGame()->getTexture(SDLApplication::CAR4); break;
	case 5: texture = game->getGame()->getTexture(SDLApplication::CAR5); break;
	}

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
