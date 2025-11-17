#pragma once
#include "game.h"
class GameObject
{
protected:
	Game* game;
public:
	GameObject();
	GameObject(Game*);
	virtual ~GameObject() = default;
	virtual void render() const;
	virtual void update();
};

