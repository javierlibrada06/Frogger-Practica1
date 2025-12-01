#include "Wasp.h"
#include "Vehicle.h"
#include "vector2D.h"
#include "PlayState.h"
#include "texture.h"

#include "FileFormatError.h"
#include <iostream>

Wasp::Wasp(std::istream& entrada, PlayState* p, PlayState::It it, std::string name)
	: SceneObject(entrada, p, name)
{
	float sX, sY;
	if (!(entrada >> sX >> sY)) throw FileFormatError(name, play->getArchiveLine(), "Error de lectura sobre la velocidad");
	speed = Vector2D<float>(sX, sY);
	int l;
	if (!(entrada >> l)) throw FileFormatError("map.txt", play->getArchiveLine(), "Error de lectura sobre el tiempo de vida de la avipa");
	texture = game->getGame()->getTexture(SDLApplication::WASP);
	liveSpawn = l;
	timeAlive = SDL_GetTicks();
	waspIterator = it;
	if (sX == 0 && sY == 0) angle = 0;
	else if (sX > 0) angle = SceneObject::ANGLE_RIGHT;
	else if (sX < 0) angle = SceneObject::ANGLE_LEFT;
	else angle = SceneObject::ANGLE_UPSIDEDOWN;
}

Wasp::~Wasp() {

}

void 
Wasp::render() const{
	texture->render(getBoundingBox(), angle);
}


void
Wasp::update() {
	if (alive) alive = isAlive();
	if (!alive) {
		GameState::DelayedCallBack d;
		d = [this]() { play->waspDelete(waspIterator); };
		game->addDelayedCallBacks(d);
		return;
	}
	else {
		position = position + (speed);
		if (position.getX() <= PlayState::GAME_END_LEFT || position.getX() >= PlayState::GAME_END_RIGHT || position.getY() <= 0 || position.getY() >= PlayState::WINDOW_HEIGHT)
		{
			alive = false;
		}
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
	Uint32 ticks = SDL_GetTicks();
	return (ticks - timeAlive < liveSpawn);
}
