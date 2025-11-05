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
	rect = { 0,0,0,0 };
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
	s = s / Game::FRAME_RATE;
	game = g;
	speed = Vector2D<float>(s, 0);
	position = Point2D<float>(posX,posY);

	switch (type)
	{
	case 1: texture = game->getTexture(Game::CAR1); break;
	case 2: texture = game->getTexture(Game::CAR2); break;
	case 3: texture = game->getTexture(Game::CAR3); break;
	case 4: texture = game->getTexture(Game::CAR4); break;
	case 5: texture = game->getTexture(Game::CAR5); break;
	}

	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
}
Game::Collision Vehicle::checkCollision(const SDL_FRect& frog) 
{
	Game::Collision collision;
	collision.type = Game::NONE;
	SDL_FRect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	if (SDL_HasRectIntersectionFloat(&frog, &rect)) {
		collision.type = Game::ENEMY;
		collision.speed = speed;
	}
	return collision;
}