#pragma once
#include "game.h"
class GameObject
{
protected:
	Game* game;
public:
	GameObject() {};
	GameObject(Game* g) : game(g) {};
	virtual ~GameObject() = default;
	virtual void render() const = 0;
	virtual void update() = 0;
};

