#pragma once
#include "Crosser.h"
#include "game.h"
class Platform : public Crosser
{
public :
	Platform(std::istream&, Game*, std::string);
	Game::Collision checkCollision(const SDL_FRect&);
};

