#include "Crosser.h"


Crosser::Crosser() {
	speed = Vector2D<float>(0, 0);
	backJump = 0;
}
Crosser::~Crosser() {

}
void 
Crosser::update() {
	rect = getBoundingBox();
	position = position + (speed);
	if (position.getX() <= Game::GAME_END_LEFT) position = Point2D<float>(Game::GAME_START_RIGHT, position.getY());
	if (position.getX() >= Game::GAME_END_RIGHT) position = Point2D<float>(Game::GAME_START_LEFT - rect.w, position.getY());
	rect.x = position.getX();
	rect.y = position.getY();
}