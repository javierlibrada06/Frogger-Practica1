#pragma once
#include "GameObject.h"
#include "vector2D.h"
#include "PlayState.h"
class SceneObject : public GameObject
{
protected:
	Point2D<float> position;
	Texture* texture;
	PlayState* play;

public:	
	SceneObject();
	SceneObject(std::istream&, PlayState*, std::string);
	virtual ~SceneObject() = default;
	void render() const;
	virtual PlayState::Collision checkCollision(const SDL_FRect& other) = 0;
protected:
	SDL_FRect getBoundingBox() const;
};

