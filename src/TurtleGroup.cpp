#include "TurtleGroup.h"
#include "texture.h"
#include "FileFormatError.h"

TurtleGroup::TurtleGroup()
	: Platform()
{
	state = 0;
	submersible = false;
	frameCounter = 0;
	numTurtles = 0;
}

TurtleGroup::TurtleGroup(std::istream& entrada, Game* g, std::string name)
	: Platform(entrada, g, name)
{
	int n, w;
	if (!(entrada >> n)) throw FileFormatError(name, g->getArchiveLine(), "Error de lectura sobre el numero de tortugas del grupo");
	if (!(entrada >> w)) throw FileFormatError(name, g->getArchiveLine(), "Error de lectura sobre el tipo de grupo tortugas");
	texture = g->getTexture(Game::TURTLE);
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

	if (frameCounter >= Game::FRAME_RATE / 2) {
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

Game::Collision
TurtleGroup::checkCollision(const SDL_FRect& frog) {
	Game::Collision c;
	c.type = Game::NONE;
	SDL_FRect rect = getBoundingBox();
	int i = 0;
	if (state == STATE_NO_SUBMERGIBLE) return c;
	else
		while (c.type != Game::PLATFORM && i < numTurtles) {
			if (SDL_HasRectIntersectionFloat(&frog, &rect)) {
				c.type = Game::PLATFORM;
				c.speed = speed;
			}
			rect.x += rect.w;
			i++;
		}
	return c;
}
