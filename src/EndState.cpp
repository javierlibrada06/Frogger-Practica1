#include "EndState.h"
#include "vector2D.h"
#include "Label.h"
#include "Button.h"
#include "MainMenuState.h"

EndState::EndState(SDLApplication* g, bool win)
	: GameState(g)
{
	if (win) gameObjects.push_back(new Label(this, Point2D<float>(SDLApplication::WINDOW_WIDTH/2, SDLApplication::WINDOW_HEIGHT / 2), SDLApplication::WIN));
	else gameObjects.push_back(new Label(this, Point2D<float>(SDLApplication::WINDOW_WIDTH / 2, SDLApplication::WINDOW_HEIGHT / 2), SDLApplication::LOSE));
	
	Button* b = new Button(this, Point2D<float>(SDLApplication::WINDOW_WIDTH / 2, SDLApplication::WINDOW_HEIGHT / 2 - 80), SDLApplication::INICIO,
		[this]() { game->replaceState(new MainMenuState(game)); });


	addEventListener(b);
	gameObjects.push_back(b);

	Button* e = new Button(this, Point2D<float>(SDLApplication::WINDOW_WIDTH / 2, SDLApplication::WINDOW_HEIGHT / 2 + 80), SDLApplication::SALIR,
		[this]() { game->exitGame(); });

	addEventListener(e);
	gameObjects.push_back(e);
}

EndState::~EndState() {
	for (GameObject* g : gameObjects) {
		delete g;
	}
}
void 
EndState::update() {

}
void 
EndState::render() const {
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) (*it)->render();
}
