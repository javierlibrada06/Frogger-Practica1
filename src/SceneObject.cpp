#include "SceneObject.h"
#include "GameObject.h"
#include "texture.h"
#include "FileFormatError.h"

SceneObject::SceneObject()
	: GameObject()
{
		position = Point2D<float>(0, 0);
		texture = nullptr;
}
SceneObject::SceneObject(std::istream& entrada, Game* g, std::string name) 
	: GameObject(g)
{
	int posX, posY;
	if (!(entrada >> posX >> posY)) throw FileFormatError(name, g->getArchiveLine(), "Error de lectura sobre la posicion");

	position = Point2D<float>(posX, posY);
}

void
SceneObject::render() const {
	texture->render(getBoundingBox());
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
