#include "Frog.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"
Frog::Frog()
{
	game = nullptr;
	texture = nullptr;
	rectCollider = { 0,0,0,0 };
	position = Point2D<float>(0, 0);
	lastPosition = Point2D<float>(0, 0);
	lives = 0;
	homesReached = 0;
	state = 0;
	angle = 0;
}

Frog::~Frog()
{
	texture = nullptr;
	game = nullptr;
}
void 
Frog::update() {
	rectCollider.x = position.getX() + Game::COLLISION_OFFSET_FROG;
	rectCollider.y = position.getY() + Game::COLLISION_OFFSET_FROG;
	Game::Collision collision = game->checkCollision(rectCollider);

	if (collision.type == Game::NONE) {
		if (position.getY() < Game::RIVER_LOW) {

			lives--;
			position = Point2D<float>(Game::FROG_INICIO, Game::GAME_SCREENEND_Y);
			lastPosition = Point2D<float>(Game::FROG_INICIO, Game::GAME_SCREENEND_Y);
			angle = 0;
		}
		if (lastPosition != position) lastPosition = position; // Actualiza la posición
	}
	else if (collision.type == Game::ENEMY) {
		lives--;
		position = Point2D<float>(Game::FROG_INICIO, Game::GAME_SCREENEND_Y);
		lastPosition = Point2D<float>(Game::FROG_INICIO, Game::GAME_SCREENEND_Y);
		angle = 0;
	}
	else if (collision.type == Game::PLATFORM) 
	{
		position = position + (collision.speed);
		if (position.getX() > Game::GAME_SCREENEND_X) position = Point2D<float>(Game::FROG_INICIO, Game::GAME_SCREENEND_Y);
		lastPosition = position;
		angle = 0;
	}
	else if (collision.type == Game::HOME) 
	{
		position = Point2D<float>(Game::FROG_INICIO, Game::GAME_SCREENEND_Y);
		lastPosition = Point2D<float>(Game::FROG_INICIO, Game::GAME_SCREENEND_Y);
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
			angle = 180;
			position = position + Point2D<float>(0, Game::FROG_STEP);
			if (position.getY() > Game::GAME_SCREENEND_Y) position = Point2D<float>(position.getX(), Game::GAME_SCREENEND_Y);
			break;
		case SDLK_UP:
			state = 1;
			angle = 0;
			position = position + Point2D<float>(0, -Game::FROG_STEP);
			if (position.getY() < 0) position = Point2D<float>(position.getX(), 0);
			break;
		case SDLK_LEFT:
			state = 1;
			angle = -90;
			position = position + Point2D<float>(-Game::FROG_STEP, 0);
			if (position.getX() < 0) position = Point2D<float>(0, position.getY());
			break;
		case SDLK_RIGHT:
			state = 1;
			angle = 90;
			position = position + Point2D<float>(Game::FROG_STEP, 0);
			if (position.getX() > Game::GAME_SCREENEND_X) position = Point2D<float>(Game::GAME_SCREENEND_X, position.getY());
			break;
		}
	}
	else state = 0;
}

void
Frog::loadFrog(std::istream& entrada, Game* g)
{
	float posX, posY;
	int l;
	entrada >> posX >> posY >> l;
	game = g;
	position = Point2D<float>(posX, posY);
	lastPosition = Point2D<float>(posX, posY);
	texture = texture = g->getTexture(Game::FROG);
	homesReached = 0;
	lives = l;

	SDL_FRect rect = getBoundingBox();
	rectCollider.x = rect.x + Game::COLLISION_OFFSET_FROG;
	rectCollider.y = rect.y + Game::COLLISION_OFFSET_FROG;
	rectCollider.h = rect.h - Game::COLLISION_OFFSET_SCREEN;
	rectCollider.w = rect.w - Game::COLLISION_OFFSET_SCREEN;

}

int
Frog::getHomesReached() const { return homesReached; }

int 
Frog::getLives() const { return lives; }

void
Frog::homeReached() { homesReached++; }

Game::Collision Frog::checkCollision(const SDL_FRect& frog)
{
	Game::Collision collision;
	collision.type = Game::NONE;
	return collision;
}

