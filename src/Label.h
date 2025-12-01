#pragma once
#include "GameObject.h"
#include "vector2D.h"
#include "SDLApplication.h"
class Label : public GameObject
{
	Point2D<float> position;
	Texture* texture;
	
public:
	Label();
	Label(GameState*, Point2D<float>, SDLApplication::TextureName);
	~Label();
	void render() const;
	void update() {};
	SDL_FRect getBoundingBox() const;
};

