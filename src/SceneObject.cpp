#include "SceneObject.h"
#include "texture.h"
//SceneObject::SceneObject() {
//	game = nullptr;
//	position = Point2D<float>(0, 0);
//	texture = nullptr;
//	rect = { 0,0,0,0 };
//	state = 0;
//	angle = 0;
//}
//
//SceneObject::SceneObject(Game* g, Point2D<float> pos, Texture* t) {
//	game = g;
//	position = pos;
//	texture = t;
//	rect = getBoundingBox();
//	state = 0;
//	angle = 0;
//}

//SceneObject::~SceneObject() {
//
//}

SDL_FRect
SceneObject::getBoundingBox() {
	SDL_FRect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	return rect;
}

void
SceneObject::render() {
	texture->renderFrame(getBoundingBox(), 0, state, angle);
}
