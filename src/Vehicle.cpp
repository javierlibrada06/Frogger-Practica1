#include "Vehicle.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"
#include <iostream>
using namespace std;
//V  50 372  -48 1

Vehicle::Vehicle()
{
	game = nullptr;
	texture = nullptr;
	speed = Vector2D<float>(0, 0);
	position = Point2D<float>(0, 0);
	rect = { 0,0,0,0 };
}
//Vehicle::Vehicle(Game* g, Point2D<float> pos, float s, int type)
//{
//	
//}
Vehicle::~Vehicle()
{
	//Eliminar Memoria
	if (texture) delete texture, texture = nullptr;
}
void 
Vehicle::update()
{
	float deltaTime = 0.05f / Game::FRAME_RATE;
	position = position + (speed*deltaTime);
	//Hay que revisar lo de delta time, Problemas para Julia y Javi del futuro :)
	if (position.getX() <= -150.0f) position = Point2D<float>(448.0f, position.getY());
	if (position.getX() >= 598.0f) position = Point2D<float>(0.0f - texture->getFrameWidth(), position.getY());
	rect.x = position.getX();
	rect.y = position.getY();
}
void 
Vehicle::render() const
{
	SDL_FRect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	texture->render(rect);
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
void 
Vehicle::loadVehicle(istream& entrada, Game* g)
{
	 float posX, posY, s;
	 int type;
	entrada >> posX >> posY >> s >> type;
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