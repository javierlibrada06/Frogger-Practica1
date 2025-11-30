#include "Log.h"
#include "Vehicle.h"
#include "vector2D.h"
#include "PlayState.h"
#include "texture.h"
#include "Crosser.h"
#include "FileFormatError.h"
#include <iostream>

Log::Log(std::istream& entrada, PlayState* g, std::string name)
	:Platform(entrada, g, name)
{
	int type;
	if (!(entrada >> type)) throw FileFormatError("map.txt", g->getArchiveLine(), "Error de lectura sobre el tipo de tronco");


	switch (type)
	{
	case 0: texture = game->getGame()->getTexture(SDLApplication::LOG1); break;
	case 1: texture = game->getGame()->getTexture(SDLApplication::LOG2); break;
	}

	backJump = 0;
}

Log::~Log()
{
	//Eliminar Memoria
	texture = nullptr;
	game = nullptr;
}

PlayState::Collision 
Log::checkCollision(const SDL_FRect& frog)
{
	PlayState::Collision collision;
	collision.type = PlayState::NONE;
	SDL_FRect rect = getBoundingBox();
	if (SDL_HasRectIntersectionFloat(&frog, &rect)){
		collision.type = PlayState::PLATFORM;
		collision.speed = speed;
	}
	return collision;
	
}

