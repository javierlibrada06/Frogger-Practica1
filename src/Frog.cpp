#include "Frog.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"
Frog::Frog()
{
	game = nullptr;
	texture = nullptr;
	position = Point2D<float>(205, 402);
	lastPosition = Point2D<float>(205, 402);
	state = 0;
	angle = 0;
	rect = { 0,0,0,0 };
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

	Game::Collision collision = game->checkCollision(rect);

	if (collision.type == Game::NONE) {
		if (position.getX() < 0.0f) position = Point2D<float>(0.0f, position.getY());
		if (position.getX() > 420.0f) position = Point2D<float>(420.0f, position.getY());
		if (position.getY() < 0.0f) position = Point2D<float>(position.getX(), 0.0f);
		if (position.getY() > 402.0f) position = Point2D<float>(position.getX(), 402.0f);
		
		if (lastPosition != position) lastPosition = position;
	}
	else if (collision.type == Game::ENEMY) {
		
		position = Point2D<float>(205, 402);
		lastPosition = Point2D<float>(205, 402);
	}
	else if (collision.type == Game::PLATFORM) 
	{
		float deltaTime = 0.05f / Game::FRAME_RATE;
		position = position + (collision.speed * deltaTime);
		if (position.getX() > 420.0f) position = Point2D<float>(205, 402);
		lastPosition = position;
	}

	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();

}
void 
Frog::handleEvent(const SDL_Event& event) {

	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
		case SDLK_DOWN:
			state = 1;
			angle = 180;
			position = position + Point2D<float>(0.0f, Game::WINDOW_HEIGHT / 15);
			break;

		case SDLK_UP:
			//texture->renderFrame(rect, 0, 1);
			state = 1;
			angle = 0;
			position = position + Point2D<float>(0.0f, -Game::WINDOW_HEIGHT/15); break;

		case SDLK_LEFT:
			//texture->renderFrame(rect, 0, 1);
			state = 1;
			angle = -90;
			position = position + Point2D<float>(-Game::WINDOW_WIDTH/15, 0.0f); break;

		case SDLK_RIGHT:
			//texture->renderFrame(rect, 0, 1);
			state = 1;
			angle = 90;
			position = position + Point2D<float>(Game::WINDOW_WIDTH/15, 0.0f); break;
		
		}
	
	}
	else state = 0;
}

void
Frog::loadFrog(std::istream& entrada, Game* g)
{
	float posX, posY, s;
	int type;
	entrada >> posX >> posY >> s >> type;
	game = g;
	position = Point2D<float>(posX, posY);
	lastPosition = Point2D<float>(posX, posY);
	texture = texture = g->getTexture(Game::FROG);
	rect.x = position.getX();
	rect.y = position.getY();
	rect.h = texture->getFrameHeight();
	rect.w = texture->getFrameWidth();
}
