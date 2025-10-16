#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"

#include "vehicle.h"

#include "log.h"

#include "frog.h"

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

	//AUX

	frog = new Frog(this);

	//Primera fila de coches
	vehicles.push_back(new Vehicle(this, Point2D<float>(50, 372), -48, 1));	
	vehicles.push_back(new Vehicle(this, Point2D<float>(200, 372), -48, 1));
	vehicles.push_back(new Vehicle(this, Point2D<float>(350, 372), -48, 1));

	//Segunda fila de coches
	vehicles.push_back(new Vehicle(this, Point2D<float>(25, 342), 48, 2));
	vehicles.push_back(new Vehicle(this, Point2D<float>(175, 342), 48, 2));
	vehicles.push_back(new Vehicle(this, Point2D<float>(325, 342), 48, 2));

	//Tercera fila de coches
	vehicles.push_back(new Vehicle(this, Point2D<float>(175, 312), -72, 3));
	vehicles.push_back(new Vehicle(this, Point2D<float>(325, 312), -72, 3));
	vehicles.push_back(new Vehicle(this, Point2D<float>(475, 312), -72, 3));

	//Cuarta fila de coches
	vehicles.push_back(new Vehicle(this, Point2D<float>(150, 280), 48, 4));
	vehicles.push_back(new Vehicle(this, Point2D<float>(0, 280), 48, 4));
	vehicles.push_back(new Vehicle(this, Point2D<float>(-150, 280), 48, 4));

	//Quinta fila de coches
	vehicles.push_back(new Vehicle(this, Point2D<float>(165, 252), -72, 5));
	vehicles.push_back(new Vehicle(this, Point2D<float>(365, 252), -72, 5));

	//----- TRONCOS -----

	//Primera fila de troncos
	logs.push_back(new Log(this, Point2D<float>(-100, 60), 72.6, 1));
	logs.push_back(new Log(this, Point2D<float>(75, 60), 72.6, 1));
	logs.push_back(new Log(this, Point2D<float>(250, 60), 72.6, 1));
	logs.push_back(new Log(this, Point2D<float>(425, 60), 72.6, 1));

	//Segunda fila de troncos
	logs.push_back(new Log(this, Point2D<float>(370, 121), 96, 1));
	logs.push_back(new Log(this, Point2D<float>(460, 121), 96, 0));
	logs.push_back(new Log(this, Point2D<float>(120, 121), 96, 1));
	logs.push_back(new Log(this, Point2D<float>(210, 121), 96, 0));
	logs.push_back(new Log(this, Point2D<float>(-130, 121), 96, 1));
	logs.push_back(new Log(this, Point2D<float>(-40, 121), 96, 0));

	//Tercera fila de troncos
	logs.push_back(new Log(this, Point2D<float>(30, 153), 48, 0));
	logs.push_back(new Log(this, Point2D<float>(180, 153), 48, 0));
	logs.push_back(new Log(this, Point2D<float>(330, 153), 48, 0));
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
