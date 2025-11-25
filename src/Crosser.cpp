#include "SceneObject.h"
#include "GameObject.h"
#include "Crosser.h"
#include "FileFormatError.h"

Crosser::Crosser(std::istream& entrada, Game* g, std::string name)
	: SceneObject(entrada, g, name)
{
	float s;
	if (!(entrada >> s)) throw FileFormatError(name, g->getArchiveLine(), "Error de lectura sobre la velocidad");
	speed = Vector2D<float>(s / Game::FRAME_RATE, 0);
	backJump = 0;
}
Crosser::~Crosser() {

}

void 
Crosser::update() {
	position = position + (speed);
	if (position.getX() <= Game::GAME_END_LEFT - backJump) position = Point2D<float>(Game::GAME_START_RIGHT + backJump, position.getY());
	if (position.getX() >= Game::GAME_END_RIGHT + backJump) position = Point2D<float>(Game::GAME_START_LEFT - getBoundingBox().w - backJump, position.getY());
}
