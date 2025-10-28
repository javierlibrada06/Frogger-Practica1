#pragma once
#include "game.h"
#include "vector2D.h"
#include "texture.h"
class Wasp
{
	Game* game;
	Texture* texture;
	Vector2D<float> speed;
	Point2D <float> position;
	SDL_FRect rect;
	Uint32 liveSpawn;
	int timeAlive;

public:
	Wasp();
	Wasp(Game*, Point2D<float>, int, Vector2D<float>);
	~Wasp();
	void update();
	void render() const;
	Game::Collision checkCollision(const SDL_FRect&);
	bool isAlive() const;
};

