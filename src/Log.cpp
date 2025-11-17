#include "Log.h"
#include "Vehicle.h"
#include "vector2D.h"
#include "game.h"
#include "texture.h"
#include "FileFormatError.h"
#include <iostream>
// L - 100  60 72.6 1

Log::Log()
	: Platform()
{
	game = nullptr;
	texture = nullptr;
	speed = Vector2D<float>(0, 0);
	position = Point2D<float>(0,0);
}

Log::Log(std::istream& entrada, Game* g, std::string name)
	:Platform(entrada, g, name)
{
	int type;
	if (!(entrada >> type)) throw FileFormatError("map.txt", g->getArchiveLine(), "Error de lectura sobre el tipo de tronco");


	switch (type)
	{
	case 0: texture = g->getTexture(Game::LOG1); break;
	case 1: texture = g->getTexture(Game::LOG2); break;
	}

	backJump = 0;
}

Log::~Log()
{
	//Eliminar Memoria
	texture = nullptr;
	game = nullptr;
}

Game::Collision Log::checkCollision(const SDL_FRect& frog)
{
	Game::Collision collision;
	collision.type = Game::NONE;
	SDL_FRect rect = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&frog, &rect)){
		collision.type = Game::PLATFORM;
		collision.speed = speed;
	}
	return collision;
	
}

