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
	bool alive;
	int angle;
	PlayState::It waspIterator;

public:
	Wasp(std::istream& entrada, PlayState*, PlayState::It, std::string name);
	~Wasp();
	void update();
	void render() const override;
	PlayState::Collision checkCollision(const SDL_FRect&);
	bool isAlive() const;
};

