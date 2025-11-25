#pragma once
#include "vector2D.h"
#include "SceneObject.h"
class Crosser : public SceneObject
{
protected:
	Vector2D<float> speed;
	int backJump;
public:
	Crosser(std::istream&, Game*, std::string);
	~Crosser();
	void update() override;
};

