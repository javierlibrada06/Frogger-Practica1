#include "InfoBar.h"
#include "Frog.h"

InfoBar::InfoBar(GameState* g, Frog* f) {
	frog = f;
	game = g;
	texture = g->getGame()->getTexture(SDLApplication::FROG);

	rect = { INFOBAR_WIDTH, INFOBAR_HEIGHT, INFOBAR_X, INFOBAR_X };

	livesRemaining = 0;
	livesSpent = 0;
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
