#pragma once
#include "GameObject.h"
#include "vector2D.h"
class SceneObject : public GameObject
{
protected:
	Point2D<float> position;
	SDL_FRect rect;
	Texture* texture;
	int state, angle;

public:
	virtual ~SceneObject() = default;
	void render();
	virtual Game::Collision checkCollision(const SDL_FRect& other) = 0;
protected:
	SDL_FRect getBoundingBox();
};

