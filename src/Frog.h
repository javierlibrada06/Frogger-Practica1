#pragma once
#include "SceneObject.h"
#include "vector2D.h"
#include "texture.h"
class Frog : public SceneObject, public EventHandler
{	
	static constexpr float FROG_INICIO = 205.0f;
	static constexpr float FROG_STEP = 32.0f;

	// FROG -- (colision offset)
	static constexpr int COLLISION_OFFSET_FROG = 3;
	static constexpr int COLLISION_OFFSET_SCREEN = 9;



	int lives;
	int homesReached;
	Point2D<float> lastPosition;
	SDL_FRect rectCollider;
	int state, angle;
public:
	Frog(std::istream&, PlayState*, std::string);
	~Frog();
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event&) override;
	int getLives() const;
	int getHomesReached() const;
	void homeReached();
	PlayState::Collision checkCollision(const SDL_FRect& frog) override;
};

