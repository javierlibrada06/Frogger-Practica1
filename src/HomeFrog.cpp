#include "HomeFrog.h"
#include "Frog.h"
#include "vector2D.h"
#include "PlayState.h"
#include "texture.h"

HomeFrog::HomeFrog(PlayState* g, Point2D<float> pos, Frog* f)
{
	frog = f;
	game = g;
	position = pos;
	texture = game->getGame()->getTexture(SDLApplication::FROG);
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

PlayState::Collision 
HomeFrog::checkCollision(const SDL_FRect& f)
{
	PlayState::Collision collision;
	collision.type = PlayState::NONE;
	SDL_FRect rect = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&f, &rect) && !active) {
		collision.type = PlayState::HOME;
		active = true;
		frog->homeReached();
	}
	return collision;

}

// Auxiliares ---

Vector2D<float>
HomeFrog::GetPosition() const { return position; }

bool
HomeFrog::IsActive() const { return active; }
