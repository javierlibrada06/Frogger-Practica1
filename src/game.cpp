#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"

#include "vehicle.h"

#include "log.h"

#include "frog.h"
#include <fstream>
#include <vector>

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "../assets/maps/default.txt";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr const char* const imgBase = "../assets/images/";

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"frog.png", 1, 2},
	{"background.png"},
	{"car1.png"},
	{"car2.png"},
	{"car3.png"},
	{"car4.png"},
	{"car5.png"},
	{"log1.png"},
	{"log2.png"},

};

Game::Game()
  : exit(false)
{
	// Carga SDL y sus bibliotecas auxiliares
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(WINDOW_TITLE,
	                          WINDOW_WIDTH,
	                          WINDOW_HEIGHT,
	                          0);

	if (window == nullptr)
		throw "window: "s + SDL_GetError();

	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr)
		throw "renderer: "s + SDL_GetError();

	// Carga las texturas al inicio
	for (size_t i = 0; i < textures.size(); i++) {
		auto [name, nrows, ncols] = textureList[i];
		textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
	}

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Game::~Game()
{
	// TODO: liberar memoria reservada por la clase
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	textures[Game::BACKGROUND]->render();
	for (int i = 0;i < vehicles.size();i++) vehicles[i]->render();
	for (int i = 0;i < logs.size();i++) logs[i]->render();
	frog->render();

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	for (int i = 0;i < vehicles.size();i++) vehicles[i]->update();
	for (int i = 0;i < logs.size();i++) logs[i]->update();
	frog->update();
	// TODO
}

void
Game::run()
{
	while (!exit) {
		// TODO: implementar bucle del juego
		handleEvents();
		render();
		update();
	}

}

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;
		frog->handleEvent(event);

		// TODO
	}
}

Game::Collision 
Game::checkCollision(const SDL_FRect& rect) const
{
	Collision collision;
	collision.type = NONE;
	int i = 0;
	while (i < vehicles.size() && collision.type == NONE) {
		collision = vehicles[i]->checkCollision(rect);
		i++;
	}
	i = 0;
	while (i < logs.size() && collision.type == NONE) {
		collision = logs[i]->checkCollision(rect);
		i++;
	}
	return collision;

}

void 
Game::loadGame() {

	 ifstream inputMap;
	 inputMap.open(MAP_FILE);
	 if (!inputMap.is_open()) cout << "No se encuentra el fichero" << endl;
	 else
	 {
		 char c;
		 while (inputMap >> c) {

			 if (c == 'V') {
				 Vehicle* v = new Vehicle();
				 v->loadVehicle(inputMap, this);
				 vehicles.push_back(v);
			 }
			 else if (c == 'L') {
				 Log* l = new Log();
				 l->loadLog(inputMap, this);
				 logs.push_back(l);
			 }
			 else if (c == 'F') {
				 Frog* f = new Frog();
				 f->loadFrog(inputMap, this);
				 frog = f;
			 }
			 //switch (c) {
			 //case 'V': 

				// break;
			 //case 'L':

				// break;
			 //}
			

		 }
		 inputMap.close();
	 }
}

