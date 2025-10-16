#include "Log.h"
#include "Vehicle.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"

// L - 100  60 72.6 1

Log::Log()
{
	game = nullptr;
	texture = nullptr;
	speed = Vector2D<float>(0, 0);
	position = Point2D<float>(0,0);
	rect = { 0,0,0,0 };
}
Log::Log(Game* g, Point2D<float> pos, float s, int type)
{
	game = g;
	speed = Vector2D<float>(s, 0);
	position = pos;

	switch (type)
	{
	case 0: texture = g->getTexture(Game::LOG1); break;
	case 1: texture = g->getTexture(Game::LOG2); break;
	}

	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
}
Log::~Log()
{
	//Eliminar Memoria
	if (texture) delete texture, texture = nullptr;
}
void
Log::update()
{
	float deltaTime = 0.05f / Game::FRAME_RATE;
	position = position + (speed * deltaTime);
	//Hay que revisar lo de delta time, Problemas para Julia y Javi del futuro :)
	if (position.getX() >= 598.0f) position = Point2D<float>(-150.0f, position.getY());
	rect.x = position.getX();
	rect.y = position.getY();
}
void
Log::render() const
{
	SDL_FRect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	texture->render(rect);
}
//Game::Collision Log::checkCollision(const SDL_FRect&)
//{
//	return;
//}