#include "Label.h"
#include "texture.h"
Label::Label() {}
Label::~Label(){}
void 
Label::render() const{
	texture->render(getBoundingBox());
}
Label::Label(GameState* g) 
	: GameObject(g)
{
	//texture = g->getTexture();
}

SDL_FRect
Label::getBoundingBox() const {
	SDL_FRect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	return rect;
}
