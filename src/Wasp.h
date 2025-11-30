#pragma once
#include "PlayState.h"
#include "SceneObject.h"
#include "vector2D.h"
#include "texture.h"

class Wasp : public SceneObject
{
	Vector2D<float> speed;
	Uint32 liveSpawn;
	int timeAlive;
	Game::It waspIterator;

public:
	Wasp(PlayState*, Point2D<float>, int, Vector2D<float>, PlayState::It);
	~Wasp();
	void update();
	PlayState::Collision checkCollision(const SDL_FRect&);
	bool isAlive() const;
};

