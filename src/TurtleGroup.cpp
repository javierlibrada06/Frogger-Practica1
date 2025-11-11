#include "TurtleGroup.h"
#include "texture.h"
TurtleGroup::TurtleGroup() {
	game = nullptr;
	texture = nullptr;
	position = Point2D<float>(0, 0);
	state = 0;
	speed = Vector2D<float>(0, 0);
	submersible = false;
	frameCounter = 0;
}
TurtleGroup::~TurtleGroup() {
	texture = nullptr;
	game = nullptr;
}
void
TurtleGroup::render() const {
	
	SDL_FRect rect = getBoundingBox();
	for (int i = 0; i < numTurtles; i++) {
		texture->renderFrame(rect, 0, state);
		rect.x += rect.w;
	}
}
void 
TurtleGroup::update() {

	frameCounter++;

	if (frameCounter >= Game::FRAME_RATE/2) {
		frameCounter = 0;

		if (submersible)
			state = (state + 1) % 7;  // 0–6
		else
			state = (state + 1) % 3;  // 0–2
	}
	Crosser::update();
}
Game::Collision
TurtleGroup::checkCollision(const SDL_FRect& frog) {
	Game::Collision c;
	c.type = Game::NONE;
	int i = 0;
	if ((state == 5)) return c;
	else
		while (c.type == Game::NONE && i < numTurtles) {
			SDL_FRect rect = getBoundingBox();
			if (SDL_HasRectIntersectionFloat(&frog, &rect)) {
				c.type = Game::PLATFORM;
				c.speed = speed;
			}
			rect.x += rect.w;
			i++;
		}
	return c;
}

void 
TurtleGroup::loadTurtle(std::istream& entrada, Game* g) {
	float posX, posY;
	int s, n, waterloggeable;
	entrada >> posX >> posY >> s >> n >> waterloggeable;
	game = g;
	position = Point2D<float>(posX, posY);
	texture = g->getTexture(Game::TURTLE);
	speed = Vector2D<float>(s / Game::FRAME_RATE, 0);
	numTurtles = n;

	submersible = waterloggeable ? 1 : 0;
}