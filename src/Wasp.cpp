#include "Wasp.h"
#include "Vehicle.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"
#include <iostream>

Wasp::Wasp(Game* g, Point2D<float> pos, int l, Vector2D<float> s, Game::It it) {
	game = g;
	texture = g->getTexture(Game::WASP);
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
		game->deleteAfter(waspIterator);  // avisa al juego para borrarse
	}
}

Game::Collision
Wasp::checkCollision(const SDL_FRect& frog) {
	Game::Collision collision;
	collision.type = Game::NONE;
	SDL_FRect rect = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&frog, &rect)) {
		collision.type = Game::ENEMY;
	}
	return collision;
}

// Auxiliares ---

bool 
Wasp::isAlive() const {
	return (SDL_GetTicks() - timeAlive < liveSpawn);
}
