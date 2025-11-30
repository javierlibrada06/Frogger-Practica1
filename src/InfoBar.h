#pragma once
#include "GameObject.h"
#include "Frog.h"
#include "game.h"
#include "texture.h"
class InfoBar : public GameObject
{
	static constexpr int INFOBAR_HEIGHT = 448;
	static constexpr int INFOBAR_WIDTH = 10;
	static constexpr int INFOBAR_X = 32;
	static constexpr int INFOBAR_Y = 32;


	int livesRemaining;
	int livesSpent;
	SDL_FRect rect;
	Frog* frog;
	GameState* game;
	Texture* texture;

public:
	InfoBar(GameState*, Frog*);
	~InfoBar();
	void update() override;
	void render() const override;
};

