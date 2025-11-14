#include "HomeFrog.h"
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
	active = false;
}

HomeFrog::HomeFrog(Game* g, Point2D<float> pos, Frog* f)
{
	frog = f;
	game = g;
	position = pos;
	texture = g->getTexture(Game::FROG);
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
		texture->renderFrame(getBoundingBox(), 0, 0);
	}
}

void
HomeFrog::update() {

}

Game::Collision HomeFrog::checkCollision(const SDL_FRect& f)
{
	Game::Collision collision;
	collision.type = Game::NONE;
	SDL_FRect rect = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&f, &rect) && !active) {
		collision.type = Game::HOME;
		active = true;
		frog->homeReached();
	}
	return collision;

}
Vector2D<float>
HomeFrog::GetPosition() const { return position; }

bool
HomeFrog::IsActive() const { return active; }