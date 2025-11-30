#pragma once
#include "vector2D.h"
#include "texture.h"
#include "Crosser.h"
class Vehicle : public Crosser
{
public:
	Vehicle(std::istream& entrada, PlayState* g, std::string);
	~Vehicle();
	PlayState::Collision checkCollision(const SDL_FRect& frog);
};

