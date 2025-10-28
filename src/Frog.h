#pragma once
#include "game.h"
#include "SceneObject.h"
#include "vector2D.h"
#include "texture.h"
class Frog : public SceneObject
{	
	int lives;
	int homesReached;
	Point2D<float> lastPosition;
	SDL_FRect rectCollider;
public:
	Frog();
	~Frog();
	//void update();
	void handleEvent(const SDL_Event&);
	void loadFrog(std::istream&, Game*);
	int GetLives() const;
	int GetHomesReached() const;
	void HomeReached();
};

