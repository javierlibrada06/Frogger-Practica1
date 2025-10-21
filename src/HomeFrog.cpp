#include "homeFrog.h"
#include "Frog.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"
HomeFrog::HomeFrog()
{
	frog = nullptr;
	game = nullptr;
	position = Point2D<float>(0,0);
	texture = nullptr;
	rect = { 0,0,0,0 };
	active = false;
}

HomeFrog::HomeFrog(Game* g, Point2D<float> pos)
{
	game = g;
	position = pos;
	texture = g->getTexture(Game::FROG);
	rect.x = position.getX();
	rect.y = position.getY();
	rect.h = texture->getFrameHeight();
	rect.w = texture->getFrameWidth();
	active = false;
}

HomeFrog::~HomeFrog() {
	texture = nullptr;
	game = nullptr;
}

void 
HomeFrog::render() const 
{
	if (active) {
		SDL_FRect rect;
		rect.x = position.getX();
		rect.y = position.getY();
		rect.h = texture->getFrameHeight();
		rect.w = texture->getFrameWidth();
		texture->renderFrame(rect, 0, 0);
	}
}

void
HomeFrog::update() {

}

Game::Collision HomeFrog::checkCollision(const SDL_FRect& frog)
{
	Game::Collision collision;
	collision.type = Game::NONE;
	SDL_FRect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	if (SDL_HasRectIntersectionFloat(&frog, &rect) && !active) {
		collision.type = Game::HOME;
		active = true;
	}
	return collision;

}