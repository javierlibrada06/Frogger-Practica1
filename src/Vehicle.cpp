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
Vehicle::Vehicle(Game* g, Texture* t, Vector2D<int> v, Point2D<int> p)
{
	game = g;
	texture = t;
	speed = v;
	position = p;
}
Vehicle::~Vehicle()
{
	//Eliminar Memoria
}
void 
Vehicle::update()
{
	render();
}
void 
Vehicle::render() const
{
	SDL_FRect rect{
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