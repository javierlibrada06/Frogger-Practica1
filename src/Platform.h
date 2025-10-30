#pragma once
#include "Crosser.h"
#include "game.h"
class Platform : public Crosser
{
public :
	using Crosser::Crosser;
	Game::Collision checkCollision(const SDL_FRect&);

};

