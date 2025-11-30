#pragma once
#include "game.h"
#include "vector2D.h"
#include "texture.h"
#include "Platform.h"
class Log : public Platform
{
	public:
	Log(std::istream& entrada, PlayState* g, std::string);
	~Log();
	PlayState::Collision checkCollision(const SDL_FRect&);
};
