#pragma once
#include "SDLApplication.h"
class GameObject
{
protected:
	GameState* game;
public:
	GameObject() : game(nullptr) {};
	GameObject(GameState* g) : game(g) {};
	virtual ~GameObject() = default;
	virtual void render() const = 0;
	virtual void update() = 0;
};

