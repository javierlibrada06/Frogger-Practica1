#pragma once
#include "game.h"
#include "SceneObject.h"
#include "vector2D.h"
#include "texture.h"
class Wasp : public SceneObject
{
	Vector2D<float> speed;
	Uint32 liveSpawn;
	int timeAlive;

public:
	Wasp();
	Wasp(Game*, Point2D<float>, int, Vector2D<float>);
	~Wasp();
	void update();
	Game::Collision checkCollision(const SDL_FRect&);
	bool isAlive() const;
};

