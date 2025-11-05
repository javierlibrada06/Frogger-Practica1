#pragma once
#include "GameObject.h"
#include "vector2D.h"
class SceneObject : public GameObject
{
protected:
	Point2D<float> position;
	Texture* texture;

public:
	virtual ~SceneObject() = default;
	void render() const override;
	virtual Game::Collision checkCollision(const SDL_FRect& other) = 0;
protected:
	SDL_FRect getBoundingBox() const;
};

