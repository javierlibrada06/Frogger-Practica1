#pragma once
#include "GameObject.h"
#include "vector2D.h"
class SceneObject : public GameObject
{
protected:
	Point2D<float> position;
	Texture* texture;

public:	
	SceneObject();
	SceneObject(std::istream&, Game*, std::string);
	virtual ~SceneObject() = default;
	void render() const;
	virtual Game::Collision checkCollision(const SDL_FRect& other) = 0;
protected:
	SDL_FRect getBoundingBox() const;
};

