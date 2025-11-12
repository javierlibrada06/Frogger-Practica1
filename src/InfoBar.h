#pragma once
#include "GameObject.h"
#include "frog.h"
#include "game.h"
#include "texture.h"
class InfoBar : public GameObject
{
	int livesRemaining;
	int livesSpent;
	SDL_FRect rect;
	Frog* frog;
	Game* game;
	Texture* texture;
public:
	InfoBar();
	void loadInfoBar(Game*, Frog*);
	~InfoBar();
	void update() override;
	void render() const override;
};

