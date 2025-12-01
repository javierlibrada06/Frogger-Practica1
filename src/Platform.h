#pragma once
#include "Crosser.h"
class Platform : public Crosser
{
public :
	Platform(std::istream&, PlayState*, std::string);
	PlayState::Collision checkCollision(const SDL_FRect&);
};

