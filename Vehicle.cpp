#include "Vehicle.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"

Vehicle::Vehicle()
{
	game;
	texture;
	speed;
	position;
}
Vehicle::Vehicle(Game* g, Point2D<float> p, float s, int type)
{
	game = g;
	speed = Vector2D<float>(s, 0);
	position = p;
	switch (type) {
	case 1:
		texture->render(Game::getTexture(Game::CAR1));
		break;
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
	/*position = position + speed;
	rect.x = position.getX();
	rect.y = position.getY();*/
}
void 
Vehicle::render() const
{
	SDL_FRect rect
	{
		rect.x = position.getX(),
		rect.y = position.getY(),
		rect.w = texture->getFrameWidth(),
		rect.h = texture->getFrameHeight()
	};
	texture->render(rect);
}
//Game::Collision Vehicle::checkCollision(const SDL_FRect&)
//{
//	return;
//}