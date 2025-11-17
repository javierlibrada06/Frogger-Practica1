#pragma once
#include "game.h"
#include "SceneObject.h"
#include "vector2D.h"
#include "texture.h"
class Frog : public SceneObject
{	
	static constexpr int ANGLE_LEFT = -90;
	static constexpr int ANGLE_RIGHT = 90;
	static constexpr int ANGLE_UPSIDEDOWN = 180;


	int lives;
	int homesReached;
	Point2D<float> lastPosition;
	SDL_FRect rectCollider;
	int state, angle;
public:
	Frog();
	Frog(std::istream&, Game*, std::string);
	~Frog();
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event&);
	int getLives() const;
	int getHomesReached() const;
	void homeReached();
	Game::Collision checkCollision(const SDL_FRect& frog) override;
};

