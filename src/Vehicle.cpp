#include "Vehicle.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"
#include <iostream>
using namespace std;

Vehicle::Vehicle()
{
	game = nullptr;
	texture = nullptr;
	speed = Vector2D<float>(0, 0);
	position = Point2D<float>(0, 0);
}
Vehicle::~Vehicle()
{
	texture = nullptr;
	game = nullptr;
}
void 
Vehicle::loadVehicle(istream& entrada, Game* g)
{
	 float posX, posY, s;
	 int type;
	entrada >> posX >> posY >> s >> type;
	speed = Vector2D<float>(s / Game::FRAME_RATE, 0);
	game = g;
	position = Point2D<float>(posX,posY);

	switch (type)
	{
	case 1: texture = game->getTexture(Game::CAR1); break;
	case 2: texture = game->getTexture(Game::CAR2); break;
	case 3: texture = game->getTexture(Game::CAR3); break;
	case 4: texture = game->getTexture(Game::CAR4); break;
	case 5: texture = game->getTexture(Game::CAR5); break;
	}
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