#include "SceneObject.h"
#include "GameObject.h"
#include "Crosser.h"


Crosser::Crosser() 
	: SceneObject()
{
	speed = Vector2D<float>(0, 0);
	backJump = 0;
}
Crosser::Crosser(std::istream& entrada, Game* g)
	: SceneObject(entrada, g)
{
	float s;
	entrada >> s;
	speed = Vector2D<float>(s / Game::FRAME_RATE, 0);
}
Crosser::~Crosser() {

}
void 
Crosser::update() {
	position = position + (speed);
	if (position.getX() <= Game::GAME_END_LEFT - backJump) position = Point2D<float>(Game::GAME_START_RIGHT + backJump, position.getY());
	if (position.getX() >= Game::GAME_END_RIGHT + backJump) position = Point2D<float>(Game::GAME_START_LEFT - getBoundingBox().w - backJump, position.getY());
}