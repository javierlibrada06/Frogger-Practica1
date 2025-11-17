#pragma once
#include "game.h"
#include "vector2D.h"
#include "texture.h"
#include "Platform.h"
class Log : public Platform
{
	public:
	Log();
	Log(std::istream& entrada, Game* g, std::string);
	~Log();
	Game::Collision checkCollision(const SDL_FRect&);
};
