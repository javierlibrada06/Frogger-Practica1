#pragma once
#include "GameObject.h"
#include "vector2D.h"
class Label : public GameObject
{
	Point2D<float> position;
	Texture* texture;
	
public:
	Label();
	Label(Game*);
	~Label();
	void render() const;
	SDL_FRect getBoundingBox() const;
};

