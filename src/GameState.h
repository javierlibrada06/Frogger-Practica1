#pragma once
#include "EventHandler.h"
#include <SDL3/SDL.h>
#include <list>
#include <functional>

class SDLApplication; 
class GameObject;
class GameState {
public: using DelayedCallBack = std::function<void()>;
	
protected:
	SDLApplication* game;
	std::list<EventHandler*> eventHandlers;
	std::list<DelayedCallBack> delayedCallBacks;
	std::list<GameObject*> gameObjects;

public:
	GameState(SDLApplication* g) : game(g) {};
	virtual ~GameState() = default;
	
	void addEventListener(EventHandler* h) { eventHandlers.push_back(h); };
	void removeEventListener(EventHandler* h) { eventHandlers.remove(h); };
	void addDelayedCallBacks(DelayedCallBack d) { delayedCallBacks.push_back(d); }

	void handleEvent(const SDL_Event& event) {
		for (EventHandler* e : eventHandlers) {
			e->handleEvent(event);
		}
	};

	void delayedCallBack() {
		for (DelayedCallBack e : delayedCallBacks) {
			e();
		}
		delayedCallBacks.clear();
	}

	virtual void update() = 0;
	virtual void render() const = 0;

	virtual void onEnter() {}
	virtual void onExit() {}

	SDLApplication* getGame() const { return game; };
};


