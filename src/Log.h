#pragma once
#include "game.h"
#include "vector2D.h"
#include "texture.h"
#include "Platform.h"
class Log : public Platform
{
	public:
	Log();
	void loadLog(std::istream& entrada, Game* g);
	~Log();
	Game::Collision checkCollision(const SDL_FRect&);
};