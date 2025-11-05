#include "Wasp.h"
#include "Vehicle.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"
#include <iostream>
Wasp::Wasp() {
	liveSpawn = 0;
	speed = Vector2D<float>(0, 0);
}

Wasp::Wasp(Game* g, Point2D<float> pos, int l, Vector2D<float> s) {
	liveSpawn = l;
	timeAlive = SDL_GetTicks();
	speed = s;
}

Wasp::~Wasp() {

}

void 
Wasp::update() {
	return GameObject::update();
}

bool 
Wasp::isAlive() const {
	return (SDL_GetTicks() - timeAlive < liveSpawn);
}

Game::Collision
Wasp::checkCollision(const SDL_FRect& frog) {
	Game::Collision collision;
	collision.type = Game::NONE;
	SDL_FRect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	if (SDL_HasRectIntersectionFloat(&frog, &rect)) {
		collision.type = Game::ENEMY;
	}
	return collision;
}