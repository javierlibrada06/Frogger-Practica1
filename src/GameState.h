#pragma once
#include <SDL3/SDL.h>

class SDLApplication; 

class GameState {
protected:
	SDLApplication* game;

public:
	GameState(SDLApplication* g) : game(g) {}
	virtual ~GameState() = default;

	virtual void handleEvent(SDL_Event& event) = 0;
	virtual void update() = 0;
	virtual void render() const = 0;

	virtual void onEnter() {}
	virtual void onExit() {}

	SDLApplication* getGame() const { return game; }
};


