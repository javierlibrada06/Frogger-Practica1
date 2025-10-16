#pragma once
#include "game.h"
#include "vector2D.h"
#include "texture.h"
class Vehicle
{
	Game* game;
	Texture* texture;
	Vector2D<float> speed;
	Point2D <float> position;
	SDL_FRect rect;

	public:
	Vehicle();
	Vehicle(Game*, Point2D<float>, float, int);
	~Vehicle();
	void update();
	void render() const;
	Game::Collision checkCollision(const SDL_FRect&);



};

