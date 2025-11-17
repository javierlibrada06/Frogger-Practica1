#include "GameObject.h"
#include "game.h"

GameObject::GameObject() {
	game = nullptr;
}

GameObject::GameObject(Game* g) {
	game = g;
}

void
GameObject::update() {

}

void
GameObject::render() const{

}
