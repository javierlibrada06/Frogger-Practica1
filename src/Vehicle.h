#pragma once
#include "game.h"
#include "vector2D.h"
class Vehicle
{
	Game* game;
	Texture* texture;
	Vector2D<int> speed;
	Point2D <int> position;
	void render() const;
	void update();
	//Collision checkCollision(const SDL_FRect&);



};

