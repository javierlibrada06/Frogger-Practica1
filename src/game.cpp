#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"

#include "vehicle.h"

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

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	for (int i = 0;i < vehicles.size();i++) vehicles[i]->update();
	// TODO
}

void
Game::run()
{
	while (!exit) {
		// TODO: implementar bucle del juego
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

		// TODO
	}
}

//Game::Collision 
//Game::checkCollision(const SDL_FRect& rect) const
//{
//	// TODO: cambiar el tipo de retorno a Collision e implementar
//	return ;
//}
