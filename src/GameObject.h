#pragma once
#include "game.h"
class GameObject
{
protected:
	Game* game;
public:
	virtual ~GameObject() = default;
	virtual void render();
	virtual void update();
};

