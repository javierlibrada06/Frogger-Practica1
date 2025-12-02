#include "TurtleGroup.h"
#include "texture.h"
#include "PlayState.h"
#include "Crosser.h"
#include "FileFormatError.h"

TurtleGroup::TurtleGroup(std::istream& entrada, PlayState* g, std::string name)
	: Platform(entrada, g, name)
{
	int n, w;
	if (!(entrada >> n)) throw FileFormatError(name, g->getArchiveLine(), "Error de lectura sobre el numero de tortugas del grupo");
	if (!(entrada >> w)) throw FileFormatError(name, g->getArchiveLine(), "Error de lectura sobre el tipo de grupo tortugas");
	texture = game->getGame()->getTexture(SDLApplication::TURTLE);
	numTurtles = n;
	submersible = w ? 1 : 0;

	state = 0;
	frameCounter = 0;
	backJump = 0;
}

TurtleGroup::~TurtleGroup() {
	texture = nullptr;
	game = nullptr;
}

void
TurtleGroup::update() {

	frameCounter++;

	if (frameCounter >= CHANGE_FRAME_DELAY) {
		frameCounter = 0;

		if (submersible)
			state = (state + 1) % STATE_SUBMERGIBLE;  // 0–6
		else
			state = (state + 1) % STATE_NO_SUBMERGIBLE_ANIM;  // 0–2
	}
	Crosser::update();
}

void
TurtleGroup::render() const {
	
	SDL_FRect rect = getBoundingBox();
	for (int i = 0; i < numTurtles; i++) {
		texture->renderFrame(rect, 0, state);
		rect.x += rect.w;
	}
}

PlayState::Collision
TurtleGroup::checkCollision(const SDL_FRect& frog) {
	PlayState::Collision c;
	c.type = PlayState::NONE;
	SDL_FRect rect = getBoundingBox();
	int i = 0;
	if (state == STATE_NO_SUBMERGIBLE) return c;
	else
		while (c.type != PlayState::PLATFORM && i < numTurtles) {
			if (SDL_HasRectIntersectionFloat(&frog, &rect)) {
				c.type = PlayState::PLATFORM;
				c.speed = speed;
			}
			rect.x += rect.w;
			i++;
		}
	return c;
}
