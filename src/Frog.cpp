#include "Frog.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"
Frog::Frog()
{
	game = nullptr;
	texture = nullptr;
	position = Point2D<float>(Game::FROG_INICIO, Game::GAME_SCREENEND_Y);
	lastPosition = Point2D<float>(Game::FROG_INICIO, Game::GAME_SCREENEND_Y);
	state = 0;
	lives = 0;
	angle = 0;
	rect = { 0,0,0,0 };
	rectCollider = { 0,0,0,0 };
	homesReached = 0;
}

Frog::~Frog()
{
	texture = nullptr;
	game = nullptr;
}

void 
Frog::render() const {
	SDL_FRect rect;
	rect.x = lastPosition.getX();
	rect.y = lastPosition.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	texture->renderFrame(rect, 0, state, angle);
}
void 
Frog::update() {
	SDL_FRect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();

	rectCollider.x = position.getX() + 3;
	rectCollider.y = position.getY() + 3;

	Game::Collision collision = game->checkCollision(rectCollider);

	if (collision.type == Game::NONE) {
		if (position.getX() < 0.0f) position = Point2D<float>(0.0f, position.getY());
		if (position.getX() > Game::GAME_SCREENEND_X) position = Point2D<float>(Game::GAME_SCREENEND_X, position.getY());
		if (position.getY() < 0.0f) position = Point2D<float>(position.getX(), 0.0f);
		if (position.getY() > Game::GAME_SCREENEND_Y) position = Point2D<float>(position.getX(), Game::GAME_SCREENEND_Y);
		if (position.getY() < Game::RIVER_LOW) {

			lives--;
			position = Point2D<float>(Game::FROG_INICIO, Game::GAME_SCREENEND_Y);
			lastPosition = Point2D<float>(Game::FROG_INICIO, Game::GAME_SCREENEND_Y);
			angle = 0;
		}
		
		if (lastPosition != position) lastPosition = position;
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

	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();

	rectCollider.x = position.getX() + 3;
	rectCollider.y = position.getY() + 3;
}
void 
Frog::handleEvent(const SDL_Event& event) {

	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
		case SDLK_DOWN:
			state = 1;
			angle = 180;
			position = position + Point2D<float>(0.0f, Game::FROG_STEP); break;

		case SDLK_UP:
			state = 1;
			angle = 0;
			position = position + Point2D<float>(0.0f, -Game::FROG_STEP); break;

		case SDLK_LEFT:
			state = 1;
			angle = -90;
			position = position + Point2D<float>(-Game::FROG_STEP, 0.0f); break;

		case SDLK_RIGHT:
			state = 1;
			angle = 90;
			position = position + Point2D<float>(Game::FROG_STEP, 0.0f); break;
		
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
	rect.x = position.getX();
	rect.y = position.getY();
	rect.h = texture->getFrameHeight();
	rect.w = texture->getFrameWidth();

	rectCollider.x = rect.x + 3;
	rectCollider.y = rect.y + 3;
	rectCollider.h = rect.h - 9;
	rectCollider.w = rect.w - 9;

}

int
Frog::GetHomesReached() { return homesReached; }

int 
Frog::GetLives() { return lives; }

void
Frog::HomeReached() { homesReached++; }

