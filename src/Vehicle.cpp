#include "Vehicle.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"

//V  50 372  -48 1

Vehicle::Vehicle()
{
	game;
	texture;
	speed;
	position;
}
Vehicle::Vehicle(Game* g, Point2D<float> pos, float s, int type)
{
	game = g;
	speed = Vector2D<float>(s, 0);
	position = pos;

	switch (type)
	{
		case 1: texture = g->getTexture(Game::CAR1); break;
		case 2: texture = g->getTexture(Game::CAR2); break;
		case 3: texture = g->getTexture(Game::CAR3); break;
		case 4: texture = g->getTexture(Game::CAR4); break;
		case 5: texture = g->getTexture(Game::CAR5); break;
	}

	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
}
Vehicle::~Vehicle()
{
	//Eliminar Memoria
}
void 
Vehicle::update()
{
	float deltaTime = 0.05f / Game::FRAME_RATE;
	position = position + (speed*deltaTime);

	if (position.getX() <= -150.0f) position = Point2D<float>(448.0f, position.getY());
	if (position.getX() >= 598.0f) position = Point2D<float>(0-texture->getFrameHeight(), position.getY());
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
//Game::Collision Vehicle::checkCollision(const SDL_FRect&)
//{
//	return;
//}