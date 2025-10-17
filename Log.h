#pragma once
#include "game.h"
#include "vector2D.h"
#include "texture.h"
class Log
{
	Game* game;
	Texture* texture;
	Vector2D<float> speed;
	Point2D <float> position;
	SDL_FRect rect;

	public:
	Log();
	void loadLog(std::istream& entrada, Game* g);
	~Log();
	void update();
	void render() const;
	Game::Collision checkCollision(const SDL_FRect&);
};