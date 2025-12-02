#pragma once
#include "GameObject.h"
#include "Frog.h"
#include "texture.h"
#include "SDL3/SDL.h"
class InfoBar : public GameObject
{
	static constexpr int INFOBAR_HEIGHT = 448;
	static constexpr int INFOBAR_WIDTH = 10;
	static constexpr int INFOBAR_X = 32;
	static constexpr int INFOBAR_Y = 32;
	static constexpr float ICON_SEPARATION = 5;


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

