#include "SceneObject.h"
#include "texture.h"

SDL_FRect
SceneObject::getBoundingBox() const {
	SDL_FRect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	return rect;
}

void
SceneObject::render() const {
	texture->render(getBoundingBox());
}
