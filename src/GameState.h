#pragma once
#include "EventHandler.h"
#include <SDL3/SDL.h>
#include <list>
#include <functional>

class SDLApplication; 

class GameState {
protected:
	SDLApplication* game;
	std::list<EventHandler*> eventHandlers;
	using DelayedCallBack = std::function<void()>;

public:
	GameState(SDLApplication* g) : game(g) {};
	virtual ~GameState() = default;
	void addEventListener(EventHandler* h) { eventHandlers.push_back(h); };
	void removeEventListener(EventHandler* h) { eventHandlers.remove(h); };

	void handleEvent(const SDL_Event& event) {
		for (EventHandler* e : eventHandlers) {
			e->handleEvent(event);
		}
	};

	virtual void update() = 0;
	virtual void render() const = 0;

	virtual void onEnter() {}
	virtual void onExit() {}

	SDLApplication* getGame() const { return game; };
};


