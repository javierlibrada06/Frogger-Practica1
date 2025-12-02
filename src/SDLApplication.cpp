#include "SDLApplication.h"
#include "PlayState.h"
#include "GameError.h"
#include "SDLError.h"

#include <array>

using namespace std;

struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr const char* const imgBase = "../assets/images/";
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";

constexpr std::array<TextureSpec, SDLApplication::NUM_TEXTURES> textureList{
	TextureSpec{"frog.png", 1, 2},
	{"background.png"},
	{"menuBackground.png"},
	{"car1.png"},
	{"car2.png"},
	{"car3.png"},
	{"car4.png"},
	{"car5.png"},
	{"log1.png"},
	{"log2.png"},
	{"wasp.png"},
	{"texts/HAS GANADO.png"},
	{"texts/GAME OVER.png"},
	{"texts/CONTINUAR.png"},
	{"texts/VOLVER AL MENÚ.png"},
	{"texts/SALIR.png"},
	{"texts/REINICIAR.png"},
	{"texts/ELIGE UN MAPA.png"},
	{"texts/Original.png"},
	{"texts/Práctica 1.png"},
	{"texts/Trivial.png"},
	{"texts/Veloz.png"},
	{"texts/Avispado.png"},
	{"texts/left.png"},
	{"texts/right.png"},
	TextureSpec{"turtle.png", 1, 7},
};

SDLApplication::SDLApplication() 
{
	// Carga SDL y sus bibliotecas auxiliares
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(WINDOW_TITLE,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0);

	if (window == nullptr) throw SDLError("No se pudo crear la ventana");

	renderer = SDL_CreateRenderer(window, nullptr);

	if (renderer == nullptr)  throw SDLError("No se pudo crear el renderer");

	// Carga las texturas al inicio
	for (size_t i = 0; i < textures.size(); i++) {
		auto [name, nrows, ncols] = textureList[i];
		textures[i] = new Texture(renderer, (string(imgBase) + name).c_str(), nrows, ncols);
	}
}

SDLApplication::~SDLApplication()
{
	for (auto t : textures) delete t;
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	SDL_Quit();
}

void
SDLApplication::run()
{
	//Delay
	const Uint32 frameDelay = TICK / FRAME_RATE;
	Uint32 frameStart;
	Uint32 frameTime;

	while (!exit) {

		// TODO: implementar bucle del juego
		frameStart = SDL_GetTicks();

		handleEvents(); //Entrada
		update();
		render();

		//Delay
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
}

void
SDLApplication::render() const
{
	SDL_RenderClear(renderer);
	GameStateMachine::render();
	SDL_RenderPresent(renderer);
}

void
SDLApplication::handleEvents() {
	
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			exit = true;
		}
		else handleEvent(event);
	}
}

void 
SDLApplication::addState(GameState* state) {
	pushState(state);
}

void SDLApplication::exitGame() {
	exit = true;
}

SDLApplication::TextureName
SDLApplication::getMapTexture(std::string name) const {
	if (name == textureList[ORIGINAL].name) return ORIGINAL;
	else if (name == textureList[TRIVIAL].name) return TRIVIAL;
	else if (name == textureList[AVISPADO].name) return AVISPADO;
	else if (name == textureList[PRACTICA_1].name) return PRACTICA_1;
	else if (name == textureList[VELOZ].name) return VELOZ;
	else if (name == textureList[LEFT_BUTTON].name) return LEFT_BUTTON;
	else if (name == textureList[RIGHT_BUTTON].name) return RIGHT_BUTTON;
	return NUM_TEXTURES;
}


