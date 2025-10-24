#pragma once
#include "game.h"
#include "vector2D.h"
#include "Frog.h"

class HomeFrog
{
	Game* game;
	Frog* frog;
	Texture* texture;
	Point2D <float> position;
	SDL_FRect rect;
	bool active;

public:
	HomeFrog();
	HomeFrog(Game*, Point2D<float>, Frog*);
	~HomeFrog();

	void render() const;
	void update(); 
	bool IsActive();
	Vector2D<float> GetPosition();
	Game::Collision checkCollision(const SDL_FRect&);
};

