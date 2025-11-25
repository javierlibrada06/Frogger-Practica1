#pragma once
#include "Platform.h"
class TurtleGroup : public Platform
{
	static constexpr int STATE_SUBMERGIBLE = 7;
	static constexpr int STATE_NO_SUBMERGIBLE = 5;
	static constexpr int STATE_NO_SUBMERGIBLE_ANIM = 3;

	int numTurtles, state;
	bool submersible;
	float frameCounter;

public:
	TurtleGroup(std::istream&, Game*, std::string);
	~TurtleGroup();
	void update() override;
	void render() const override;
	Game::Collision checkCollision(const SDL_FRect&) override;
};

