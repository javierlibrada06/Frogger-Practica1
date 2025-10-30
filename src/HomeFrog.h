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
	HomeFrog();
	HomeFrog(Game*, Point2D<float>, Frog*);
	~HomeFrog();

	void render() const;
	void update(); 
	bool IsActive() const;
	Vector2D<float> GetPosition() const;
};

