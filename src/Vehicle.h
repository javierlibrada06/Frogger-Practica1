#pragma once
#include "game.h"
#include "vector2D.h"
#include "texture.h"
class Vehicle
{
	Game* game;
	Texture* texture;
	Vector2D<int> speed;
	Point2D <int> position;

	public:
	Vehicle();
	Vehicle(Game*, Texture*,Vector2D<int>, Point2D<int>);
	~Vehicle();
	void update();
	void render() const;
	Game::Collision checkCollision(const SDL_FRect&);



};

