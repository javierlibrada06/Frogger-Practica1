#pragma once
#include "Platform.h"
class TurtleGroup : public Platform
{

	int numTurtles, state;
	bool submersible;
	float frameCounter;

public:
	TurtleGroup();
	~TurtleGroup();
	void update();
	void render() const override;
	Game::Collision checkCollision(const SDL_FRect&) override;
	void loadTurtle(std::istream&, Game*);
};

