#include "GameState.h"
#include "GameObject.h"

#include <list>

#pragma once
class EndState : public GameState
{
	static constexpr float COLOR_VALUE = 255;
	static constexpr float LABEL_POSX = SDLApplication::WINDOW_WIDTH / 2;
	static constexpr float LABEL_POSY = SDLApplication::WINDOW_HEIGHT / 2;
	static constexpr float LABEL_SEPARATION = 80;

public:
	EndState(SDLApplication* g, bool);
	//void handleEvent(SDL_Event& event) override;
	void handleEvent(const SDL_Event& event) override { GameState::handleEvent(event); };

};

