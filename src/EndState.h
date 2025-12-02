#include "GameState.h"
#include "GameObject.h"

#include <list>

#pragma once
class EndState : public GameState
{
	constexpr static float COLOR_VALUE = 255;
	constexpr static float LABEL_POSX = SDLApplication::WINDOW_WIDTH / 2;
	constexpr static float LABEL_POSY = SDLApplication::WINDOW_HEIGHT / 2;
	constexpr static float LABEL_SEPARATION = 80;
	std::list<GameObject*> gameObjects;

public:
	EndState(SDLApplication* g, bool);
	~EndState();
	//void handleEvent(SDL_Event& event) override;
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override { GameState::handleEvent(event); };

};

