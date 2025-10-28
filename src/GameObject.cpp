#include "GameObject.h"
#include "game.h"

GameObject::GameObject() {
	game = nullptr;
}
GameObject::GameObject(Game* g) {
	game = g;
}

GameObject::~GameObject() {

}

void
GameObject::render() const {

}

void 
GameObject::update() {

}
