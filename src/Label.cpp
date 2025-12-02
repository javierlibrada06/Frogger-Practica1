#include "Label.h"
#include "texture.h"
#include "SDLApplication.h"
#include "InfoBar.h"
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
void
Label::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	texture->setColorMod(r, g, b);
}

SDL_FRect
Label::getBoundingBox() const {
	SDL_FRect rect;
	rect.x = position.getX()- texture->getFrameWidth() / HALF;
	rect.y = position.getY() - texture->getFrameHeight() / HALF;
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	return rect;
}
