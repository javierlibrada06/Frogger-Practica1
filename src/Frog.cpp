#include "Frog.h"
#include "vector2D.h"
#include "PlayState.h"
#include "texture.h"
#include "FileFormatError.h"

Frog::Frog(std::istream& entrada, PlayState* g, std::string name)
	: SceneObject(entrada, g, name)
{
	int l;
	if (!(entrada >> l)) throw FileFormatError(name, play->getArchiveLine(), "Error de lectura sobre las vidas de la tortuga");

	lastPosition = position;
	texture = game->getGame()->getTexture(SDLApplication::FROG);
	homesReached = 0;
	lives = l;
	state = 0;
	angle = 0;

	SDL_FRect rect = getBoundingBox();
	rectCollider.x = rect.x + COLLISION_OFFSET_FROG;
	rectCollider.y = rect.y + COLLISION_OFFSET_FROG;
	rectCollider.h = rect.h - COLLISION_OFFSET_SCREEN;
	rectCollider.w = rect.w - COLLISION_OFFSET_SCREEN;

}

Frog::~Frog()
{
	texture = nullptr;
	game = nullptr;
}

void 
Frog::update() {
	rectCollider.x = position.getX() + COLLISION_OFFSET_FROG;
	rectCollider.y = position.getY() + COLLISION_OFFSET_FROG;
	PlayState::Collision collision = play->checkCollision(rectCollider);

	if (collision.type == PlayState::NONE) {
		if (position.getY() < PlayState::RIVER_LOW) {

			lives--;
			position = Point2D<float>(FROG_INICIO, PlayState::GAME_SCREENEND_Y);
			lastPosition = Point2D<float>(FROG_INICIO, PlayState::GAME_SCREENEND_Y);
			angle = 0;
		}
		if (lastPosition != position) lastPosition = position; // Actualiza la posición
	}
	else if (collision.type == PlayState::ENEMY) {
		lives--;
		position = Point2D<float>(FROG_INICIO, PlayState::GAME_SCREENEND_Y);
		lastPosition = Point2D<float>(FROG_INICIO, PlayState::GAME_SCREENEND_Y);
		angle = 90;
	}
	else if (collision.type == PlayState::PLATFORM)
	{
		position = position + (collision.speed);
		if (position.getX() > PlayState::GAME_SCREENEND_X) position = Point2D<float>(FROG_INICIO, PlayState::GAME_SCREENEND_Y);
		lastPosition = position;
		angle = 0;
	}
	else if (collision.type == PlayState::HOME)
	{
		play->homeReached(position);
		position = Point2D<float>(FROG_INICIO, PlayState::GAME_SCREENEND_Y);
		lastPosition = Point2D<float>(FROG_INICIO, PlayState::GAME_SCREENEND_Y);
		angle = 0;
	}
}

void
Frog::render() const {
	texture->renderFrame(getBoundingBox(), 0, state, angle);

}

void 
Frog::handleEvent(const SDL_Event& event) {

	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
		case SDLK_DOWN:
			state = 1;
			angle = SceneObject::ANGLE_UPSIDEDOWN;
			position = position + Point2D<float>(0, FROG_STEP);
			if (position.getY() > PlayState::GAME_SCREENEND_Y) position = Point2D<float>(position.getX(), PlayState::GAME_SCREENEND_Y);
			break;
		case SDLK_UP:
			state = 1;
			angle = 0;
			position = position + Point2D<float>(0, -FROG_STEP);
			if (position.getY() < 0) position = Point2D<float>(position.getX(), 0);
			break;
		case SDLK_LEFT:
			state = 1;
			angle = SceneObject::ANGLE_LEFT;
			position = position + Point2D<float>(-FROG_STEP, 0);
			if (position.getX() < 0) position = Point2D<float>(0, position.getY());
			break;
		case SDLK_RIGHT:
			state = 1;
			angle = SceneObject::ANGLE_RIGHT;
			position = position + Point2D<float>(FROG_STEP, 0);
			if (position.getX() > PlayState::GAME_SCREENEND_X) position = Point2D<float>(PlayState::GAME_SCREENEND_X, position.getY());
			break;
		case SDLK_ESCAPE:
			play->pause();
			break;
		}
	}
	else state = 0;
}

PlayState::Collision
Frog::checkCollision(const SDL_FRect& frog)
{
	PlayState::Collision collision;
	collision.type = PlayState::NONE;
	return collision;
}

int
Frog::getHomesReached() const { return homesReached; }

int 
Frog::getLives() const { return lives; }

void
Frog::homeReached() { homesReached++;}

