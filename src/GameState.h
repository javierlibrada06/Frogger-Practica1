#include <list>
#include "GameObject.h"
#include "EventHandler.h"
#include "Game.h"
#pragma once

class GameState
{
	Game* game;
	std::list<GameObject*> gameObjects;
	std::list<EventHandler*> eventHandlers;
	//std::list<DelayedCallBack> delayedCallBacks;

public:
	GameState();
	GameState(Game* g) : game(g) {};
	~GameState() = default;

	void update();
	void render() const;
	void handleEvent();
	void addEventListener();
	void addObject();
	Game getGame() const;

};

