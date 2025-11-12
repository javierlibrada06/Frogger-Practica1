#include "InfoBar.h"
#include "frog.h"
#include "game.h"
void
InfoBar::loadInfoBar(Game* g, Frog* f) {
	frog = f;
	game = g;
	texture = g->getTexture(Game::FROG);
	rect = { 10, Game::WINDOW_HEIGHT - 40, 32, 32 };
	livesRemaining = 0;
	livesSpent = 0;
}
InfoBar::InfoBar() {
	frog = nullptr;
	rect = {0,0,0,0};
	texture = nullptr;
	livesRemaining = 0;
	livesSpent = 0;
	game = nullptr;
}
InfoBar::~InfoBar() {

}
void 
InfoBar::update() {
	livesRemaining = frog->getLives();
}
void 
InfoBar::render() const {
	float iconWidth = texture->getFrameWidth();
	for (int i = 0; i < livesRemaining; i++) {
		SDL_FRect pos = { rect.x + i * (iconWidth + 5), rect.y, iconWidth, iconWidth };
		texture->renderFrame(pos, 0, 0);
	}
}