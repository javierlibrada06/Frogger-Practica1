#pragma once
#include "game.h"
#include "vector2D.h"
#include "texture.h"
class Frog
{
	Game* game;
	Texture* texture;
	Point2D<float> lastPosition;
	Point2D <float> position;
	int lives;
	SDL_FRect rect;
public:
	Frog();
	//Frog(Game*);
	~Frog();
	void render() const;
	void update();
	void handleEvent(const SDL_Event&);
	void loadFrog(std::istream&, Game*);
};

