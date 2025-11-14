#include "game.h"
#include "texture.h"
#include "Vehicle.h"
#include "Log.h"
#include "HomeFrog.h"
#include "Wasp.h"
#include "TurtleGroup.h"
#include "Frog.h"
#include "SceneObject.h"
#include "infoBar.h"

#include <string>
#include <SDL3_image/SDL_image.h>
#include <fstream>
#include <vector>
#include <random>

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
	{"wasp.png"},
	TextureSpec{"turtle.png", 1, 7},

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

	nextWasp = getRandomRange(MIN_WASP_GENERATOR, MAX_WASP_GENERATOR);
	waspSpawn = SDL_GetTicks();

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Game::~Game()
{
	for (SceneObject* s : sceneObjects) {
		delete s;     
	}
	sceneObjects.clear();
	homeFrogs.clear();
	delete frog;
	delete infoBar;
	for (auto t : textures) {
		delete t;
	}

	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	SDL_Quit();
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	textures[Game::BACKGROUND]->render();

	for(auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) (*it)->render();
	frog->render();
	infoBar->render();
	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	waspUpdate();
	for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) (*it)->update();
	frog->update();
	infoBar->update();

	// Aqui se eliminan todas las avispas muertas
	waspDelete();
}

void
Game::run()
{
	const Uint32 frameDelay = TICK / FRAME_RATE;
	Uint32 frameStart;
	Uint32 frameTime;

	while (!exit) {
		// TODO: implementar bucle del juego

		frameStart = SDL_GetTicks();
		if (frog->getHomesReached() == NUMBER_HFROGS)
		{
			cout << "Has alcanzado todos los nidos" << endl;
			exit = true;
		}
		else if (frog->getLives() == 0)
		{
			cout << "Te has quedado sin vidas (0/3)" << endl;
			exit = true;
		}
		handleEvents();
		update();
		render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
}

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			exit = true;
		}
		/*else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_0) confirmReset();*/
		frog->handleEvent(event);

		// TODO
	}
}

Game::Collision 
Game::checkCollision(const SDL_FRect& rect) const
{
	Collision collision;
	collision.type = NONE;
	auto it = sceneObjects.begin();
	while (it != sceneObjects.end() && collision.type == NONE) {
		collision = (*it)->checkCollision(rect);
		it++;
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
				 sceneObjects.push_back(v);
			 }
			 else if (c == 'L') {
				 Log* l = new Log();
				 l->loadLog(inputMap, this);
				 sceneObjects.push_back(l);
			 }
			 else if (c == 'T') {
				 TurtleGroup* t = new TurtleGroup();
				 t->loadTurtle(inputMap, this);
				 sceneObjects.push_back(t);
			 }
			 else if (c == 'F') {
				 frog = new Frog();
				 frog->loadFrog(inputMap, this);
			 }
			 else inputMap.ignore('#', '\n');
		 }
		 
		 inputMap.close();
	 }

	 infoBar = new InfoBar();
	 infoBar->loadInfoBar(this, frog);

	 for (int i = 0; i < NUMBER_HFROGS; i++)
	 {
		 HomeFrog* homeFrog = new HomeFrog(this, homeFrogsPos[i], frog);
		 homeFrogs.push_back(homeFrog);
		 sceneObjects.push_back(homeFrog);
	 }
	 
}

int 
Game::getRandomRange(int min, int max) {
	static std::random_device rd;
	static std::mt19937 randomGenerator(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(randomGenerator);
}

void
Game::waspUpdate() {
	if (SDL_GetTicks() - waspSpawn >= nextWasp)
	{
		waspSpawn = SDL_GetTicks();
		if (frog->getHomesReached() != Game::NUMBER_HFROGS - 1)
		{
			// Genera nueva avispa
			nextWasp = (float)getRandomRange(MIN_WASP_GENERATOR, MAX_WASP_GENERATOR);
			float lifeTime = (float)getRandomRange(MIN_WASP_LIFE, MAX_WASP_LIFE);
			bool encontrado = false;
			int hf = getRandomRange(0, Game::NUMBER_HFROGS - 1);
			while (!encontrado)
			{
				if (!homeFrogs[hf]->IsActive()) encontrado = true;
				else {
					hf++;
					if (hf > Game::NUMBER_HFROGS - 1) hf = 0;
				}
			}
			Point2D<float> pos = homeFrogs[hf]->GetPosition();
			pos = pos + Point2D<float>(Game::WASP_OFFSET_X, Game::WASP_OFFSET_Y);
			Vector2D<float> speed(0, 0);
			
			sceneObjects.push_back(nullptr);  // reserva un hueco
			It it = --sceneObjects.end();
			*it = new Wasp(this, pos, lifeTime, speed, it);
			//sceneObjects.push_back(new Wasp(this, pos, lifeTime, speed));
		}
	}
}

// Método para guardar los it de avispas a eliminar, para eliminar al terminar el update
void 
Game::deleteAfter(It it) {

	waspToDelete.push_back(it);
}

void
Game::waspDelete()
{
	for (auto it : waspToDelete) {
		delete* it;             // primero liberar memoria
		sceneObjects.erase(it); // luego borrar de la lista
	}
	waspToDelete.clear();       // vaciar vector
}

void
Game::reset() {
	for (SceneObject* s : sceneObjects) {
		delete s;
	}
	sceneObjects.clear();
	delete frog;
	delete infoBar;
	loadGame();
}

void
Game::confirmReset() {

	SDL_MessageBoxButtonData buttons[] = {
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Aceptar" },
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Cancelar" }
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, 
		NULL,                        
		"Quieres reiniciar la partida?",        
		"Pulsa Aceptar para reiniciar la partida.",
		SDL_arraysize(buttons),       
		buttons,                      
		NULL                          // Esquema de colores 
	};

	int buttonid = -1;

	// Mostrar la caja de mensaje
	SDL_ShowMessageBox(&messageboxdata, &buttonid);
	if (buttonid == 1) {
		reset();
	}
}