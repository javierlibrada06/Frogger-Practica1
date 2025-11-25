#include "Vehicle.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"
#include "FileFormatError.h"
#include <iostream>
using namespace std;

Vehicle::Vehicle(istream& entrada, Game* g, std::string name)
	: Crosser(entrada, g, name)
{
	int type;
	if (!(entrada >> type)) throw FileFormatError(name, g->getArchiveLine(), "Error de lectura sobre el tipo de coche");

	switch (type)
	{
	case 1: texture = game->getTexture(Game::CAR1); break;
	case 2: texture = game->getTexture(Game::CAR2); break;
	case 3: texture = game->getTexture(Game::CAR3); break;
	case 4: texture = game->getTexture(Game::CAR4); break;
	case 5: texture = game->getTexture(Game::CAR5); break;
	}

	backJump = 0;
}

Vehicle::~Vehicle()
{
	texture = nullptr;
	game = nullptr;
}

Game::Collision Vehicle::checkCollision(const SDL_FRect& frog) 
{
	Game::Collision collision;
	collision.type = Game::NONE;
	SDL_FRect rect = getBoundingBox();

	if (SDL_HasRectIntersectionFloat(&frog, &rect)) {
		collision.type = Game::ENEMY;
		collision.speed = speed;
	}
	return collision;
}
