#include "GameState.h"
#include "GameObject.h"

#include <list>

#pragma once
class EndState : public GameState
{
	std::list<GameObject*> gameObjects;

public:
	EndState(SDLApplication* g, bool);
	~EndState();
	void handleEvent(SDL_Event& event) override;
	void update() override;
	void render() const override;
};

