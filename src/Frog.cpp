#include "Frog.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"

Frog::Frog()
{
	game = nullptr;
	texture = nullptr;
	position = Point2D<float>(50, 402);
	lastPosition = Point2D<float>(50, 402);
	rect = { 0,0,0,0 };
}

Frog::Frog(Game* g)
{
	game = g;
	texture = texture = g->getTexture(Game::FROG);
	position = Point2D<float>(50, 402);
	lastPosition = Point2D<float>(50, 402);
	rect = { 0,0,0,0 };
}

Frog::~Frog()
{
	//Eliminar Memoria
	if (texture) delete texture, texture = nullptr;
}

void 
Frog::render() const {
	SDL_FRect rect;
	rect.x = lastPosition.getX();
	rect.y = lastPosition.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	texture->renderFrame(rect, 0, 0);
}
void 
Frog::update() {

	if (position.getX() < 0.0f) position = Point2D<float>(0.0f, position.getY());
	if (position.getX() > 420.0f) position = Point2D<float>(420.0f, position.getY());
	if (position.getY() < 0.0f) position = Point2D<float>(position.getX(), 0.0f);
	if (position.getY() > 402.0f) position = Point2D<float>(position.getX(), 402.0f);
	if (lastPosition != position) lastPosition = position;

}
void 
Frog::handleEvent(const SDL_Event& event) {

	if ((event.key.key == SDLK_DOWN)) position = position + Point2D<float>(0.0f, 16.0f);
	else if ((event.key.key == SDLK_UP)) position = position + Point2D<float>(0.0f, -16.0f);
	else if ((event.key.key == SDLK_LEFT)) position = position + Point2D<float>(-12.0f, 0.0f);
	else if ((event.key.key== SDLK_RIGHT)) position = position + Point2D<float>(12.0f, 0.0f);
}