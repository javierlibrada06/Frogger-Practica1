#pragma once
#include "Vector2D.h"
#include "src/game.h"
#include "src/texture.h"

class Frog
{
	Game* game;
	Texture* texture;
	Vector2D<int> position;
	int lives;
public:
	Frog();
	~Frog();
	void Render();
	void Update();
	void Move();
	bool CheckCollision();
	void HandleEvent(const SDL_Event&);

};

