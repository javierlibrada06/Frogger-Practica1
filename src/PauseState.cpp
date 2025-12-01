
#include "PauseState.h"
#include "Button.h"
#include "texture.h"
#include "MainMenuState.h"
#include "SceneObject.h"
#include "PlayState.h"
#include <string>
#include <list>

PauseState::PauseState(SDLApplication* g, std::string name, std::list<SceneObject*> list)
	: GameState(g), sceneObjects(list)
{
	//Texture* background = new Texture(r);
	Button* b = new Button(this, Point2D<float>(SDLApplication::WINDOW_WIDTH / 2, SDLApplication::WINDOW_HEIGHT / 2 - 150 ), SDLApplication::CONTINUE,
		[this, name, list]() { game->popState(); });

	addEventListener(b);
	gameObjects.push_back(b);

	std::list<SceneObject*> l;
	b = new Button(this, Point2D<float>(SDLApplication::WINDOW_WIDTH / 2, SDLApplication::WINDOW_HEIGHT / 2 - 75), SDLApplication::REINICIAR,
		[this, name, l]() { game->replaceState(new PlayState(game, name, l)); });

	addEventListener(b);
	gameObjects.push_back(b);

	b = new Button(this, Point2D<float>(SDLApplication::WINDOW_WIDTH / 2, SDLApplication::WINDOW_HEIGHT / 2 + 75 ), SDLApplication::INICIO,
		[this]() { game->replaceState(new MainMenuState(game));  });

	addEventListener(b);
	gameObjects.push_back(b);


	b = new Button(this, Point2D<float>(SDLApplication::WINDOW_WIDTH / 2, SDLApplication::WINDOW_HEIGHT / 2 + 150), SDLApplication::SALIR,
		[this]() { game->exitGame(); });

	addEventListener(b);
	gameObjects.push_back(b);

}
PauseState::~PauseState() {
	for (GameObject* g : gameObjects) {
		delete g;
	}
}
void 
PauseState::update() {

}
void 
PauseState::render() const {
	
	game->getTexture(SDLApplication::BACKGROUND)->render();
	for (auto s : sceneObjects) s->render();
	SDL_FRect fullScreenRect = { 0, 0, 448, 484 };
	SDL_Color dim = { 0, 0, 0, 130 };
	game->getTexture(SDLApplication::BACKGROUND)->render(fullScreenRect, dim, 130);
	for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) (*it)->render();
}
