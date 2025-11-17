#include "SceneObject.h"
#include "GameObject.h"
#include "texture.h"

SceneObject::SceneObject()
	: GameObject()
{
		position = Point2D<float>(0, 0);
		texture = nullptr;
}
SceneObject::SceneObject(std::istream& entrada, Game* g) 
	: GameObject(g)
{
	int posX, posY;
	entrada >> posX >> posY;

	position = Point2D<float>(posX, posY);
}

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
