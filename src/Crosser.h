#pragma once
#include "vector2D.h"
#include "SceneObject.h"
class Crosser : public SceneObject
{
protected:
	Vector2D<float> speed;
	int backJump;
public:
	Crosser();
	~Crosser();
	void update() override;
};

