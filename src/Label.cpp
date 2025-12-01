#include "Label.h"
#include "texture.h"
#include "SDLApplication.h"
Label::Label() {}
Label::~Label(){}
void 
Label::render() const{
	texture->render(getBoundingBox());
}
Label::Label(GameState* g, Point2D<float> p, SDLApplication::TextureName t)
	: GameObject(g), position(p), texture (g->getGame()->getTexture(t))
{
	//texture = g->getGame()->getTexture(SDLApplic);
}

SDL_FRect
Label::getBoundingBox() const {
	SDL_FRect rect;
	rect.x = position.getX()- texture->getFrameWidth() / 2;
	rect.y = position.getY() - texture->getFrameHeight() / 2;
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	return rect;
}
