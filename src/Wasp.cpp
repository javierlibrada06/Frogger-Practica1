#include "Wasp.h"
#include "Vehicle.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"
#include <iostream>
Wasp::Wasp() {
	game = nullptr;
	texture = nullptr;
	position = Point2D<float>(0, 0);
	liveSpawn = 0.0f;
	speed = Vector2D<float>(0, 0);
}

Wasp::Wasp(Game* g, Point2D<float> pos, int l, Vector2D<float> s) {
	game = g;
	texture = g->getTexture(Game::WASP);
	position = pos;
	liveSpawn = l;
	timeAlive = SDL_GetTicks();
	speed = s;
}

Wasp::~Wasp() {
	texture = nullptr;
	game = nullptr;
}

void 
Wasp::update() {
	float deltaTime = Game::TICK / Game::FRAME_RATE;
	position = position + (speed * deltaTime);
}

void 
Wasp::render() const {
	SDL_FRect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	texture->render(rect);
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

bool 
Wasp::isAlive() {
	return (SDL_GetTicks() - timeAlive < liveSpawn);
}