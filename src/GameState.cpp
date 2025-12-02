#include "GameState.h"
#include "GameObject.h"
#include "SDLApplication.h"

GameState::GameState(SDLApplication* g)
	: game(g) {
};
GameState::~GameState() {
	for (GameObject* g : gameObjects) delete(g);
}
void 
GameState::addEventListener(EventHandler* h) { eventHandlers.push_back(h); };
void 
GameState::removeEventListener(EventHandler* h) { eventHandlers.remove(h); };
void 
GameState::addDelayedCallBacks(DelayedCallBack d) { delayedCallBacks.push_back(d); }

void 
GameState::handleEvent(const SDL_Event& event) {
	for (EventHandler* e : eventHandlers) {

		e->handleEvent(event);
	}
}

void 
GameState::delayedCallBack() {
	for (DelayedCallBack e : delayedCallBacks) {
		e();
	}
	delayedCallBacks.clear();
}

void 
GameState::update() {

};
void
GameState::render() const {
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) { (*it)->render(); }
}

void 
GameState::onEnter() {}
void 
GameState::onExit() {}

SDLApplication* 
GameState::getGame() const {
	return game; 
}
