#include "Frog.h"
#include "Vector2D.h"

Frog::Frog(Game* actualGame, Texture* frogTexture, Vector2D<int>& frogPosition, int amount)
{
	game = actualGame;
	texture = frogTexture;
	position = frogPosition;
	lives = amount;
}

Frog::~Frog() 
{

}

void Frog::Render()
{
	texture->Texture::render();
}

void Frog::Update()
{

}

void Frog::Move() 
{

}

bool Frog::CheckCollision()
{

}
void Frog::HandleEvent(const SDL_Event&) {

}
