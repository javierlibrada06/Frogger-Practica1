#include "Wasp.h"
#include "Vehicle.h"
#include "vector2D.h"
#include "PlayState.h"
#include "texture.h"
#include <iostream>

Wasp::Wasp(PlayState* g, Point2D<float> pos, int l, Vector2D<float> s, Game::It it) {
	game = g;
	texture = game->getGame()->getTexture(SDLApplication::WASP);
	position = pos;
	liveSpawn = l;
	timeAlive = SDL_GetTicks();
	speed = s;
	waspIterator = it;
}

Wasp::~Wasp() {

}

void
Wasp::update() {
	if (!isAlive()) {
		//play->deleteAfter(waspIterator);  // avisa al juego para borrarse
	}
}

PlayState::Collision
Wasp::checkCollision(const SDL_FRect& frog) {
	PlayState::Collision collision;
	collision.type = PlayState::NONE;
	SDL_FRect rect = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&frog, &rect)) {
		collision.type = PlayState::ENEMY;
	}
	return collision;
}

// Auxiliares ---

bool 
Wasp::isAlive() const {
	return (SDL_GetTicks() - timeAlive < liveSpawn);
}
