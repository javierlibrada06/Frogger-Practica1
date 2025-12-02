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
	GameState(SDLApplication* g);
	virtual ~GameState();
	
	void addEventListener(EventHandler* h);
	void removeEventListener(EventHandler* h);
	void addDelayedCallBacks(DelayedCallBack d);

	virtual void handleEvent(const SDL_Event& event);

	void delayedCallBack();
	virtual void update();
	virtual void render() const;

	virtual void onEnter();
	virtual void onExit();

	SDLApplication* getGame() const;
};


