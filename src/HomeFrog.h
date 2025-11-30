#pragma once
#include "game.h"
#include "vector2D.h"
#include "Frog.h"
#include "SceneObject.h"
class HomeFrog : public SceneObject
{
	Frog* frog;
	bool active;

public:
	HomeFrog(PlayState*, Point2D<float>, Frog*);
	~HomeFrog();
	void render() const override;
	void update() override {};
	bool IsActive() const;
	Vector2D<float> GetPosition() const;
	PlayState::Collision checkCollision(const SDL_FRect& f) override;
};

