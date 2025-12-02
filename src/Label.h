#pragma once
#include "GameObject.h"
#include "vector2D.h"
#include "SDLApplication.h"
#include "texture.h"
#include "SDL3/SDL.h"
class Label : public GameObject
{
protected:
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

