#include "GameObject.h"
#include "game.h"

GameObject::GameObject() {
	game = nullptr;
}

GameObject::GameObject(Game* g) {
	game = g;
}

void
GameObject::render() const{

}

void
GameObject::update() {

}