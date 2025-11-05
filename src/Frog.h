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
	int state, angle;
public:
	Frog();
	~Frog();
	void update();
	void render() const override;
	void handleEvent(const SDL_Event&);
	void loadFrog(std::istream&, Game*);
	int getLives() const;
	int getHomesReached() const;
	void homeReached();
	Game::Collision checkCollision(const SDL_FRect& frog);
};

