#pragma once
#include "Crosser.h"
#include "game.h"
class Platform : public Crosser
{
public :
	Platform();
	Platform(std::istream&, Game*);
	Game::Collision checkCollision(const SDL_FRect&);
};

