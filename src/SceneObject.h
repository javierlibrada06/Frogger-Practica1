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
	SceneObject();
	SceneObject(Game*, Point2D<float>, Texture*);
	~SceneObject();
	
	void render();
	bool checkCollision(SDL_FRect);
	SDL_FRect getBoundingBox();
};

