#include "game.h"

#include <string>

#include <SDL3_image/SDL_image.h>

#include "texture.h"

#include "vehicle.h"

#include "log.h"

#include "HomeFrog.h"

#include "Wasp.h"

#include "frog.h"

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

	nextWasp = getRandomRange(1,30);

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Game::~Game()
{
	for (Vehicle* v : vehicles) {
		delete v;     
	}
	vehicles.clear();
	for (Log* l : logs) {
		delete l;
	}
	logs.clear();
	for (HomeFrog* h : homeFrogs) {
		delete h;
	}
	homeFrogs.clear();
	for (Wasp* w : wasps) {
		delete w;
	}
	wasps.clear();
	delete frog;
	for (auto t : textures) {
		delete t;
	}
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	textures[Game::BACKGROUND]->render();
	for (int i = 0;i < vehicles.size();i++) vehicles[i]->render();
	for (int i = 0;i < logs.size();i++) logs[i]->render();
	for (int i = 0; i < homeFrogs.size(); i++) homeFrogs[i]->render();
	for (int i = 0; i < wasps.size(); i++) wasps[i]->render();
	frog->render();
	SDL_RenderPresent(renderer);
}

void
Game::update()
{

	float deltaTime = 0.05f / Game::FRAME_RATE;
	if (nextWasp > 0) nextWasp = nextWasp - (1 * deltaTime);
	else
	{
		// Aqui se eliminan todas las avispas muertas
		for (int i = (int)wasps.size() - 1; i >= 0; i--)
		{
			if (!wasps[i]->isAlive())
			{
				delete wasps[i];
				wasps[i] = wasps.back();
				wasps.pop_back();
			}
		}
		if (wasps.size() == 0 && frog->GetHomesReached() != 4)
		{
			// Genera nueva avispa
			float lifeTime = (float)getRandomRange(5, 20);
			nextWasp = (float)getRandomRange(5, 10);
			bool encontrado = false;
			int hf = 0;
			while (!encontrado)
			{
				hf = getRandomRange(0, 4);
				if (!homeFrogs[hf]->IsActive()) encontrado = true;
			}
			Point2D<float> pos = homeFrogs[hf]->GetPosition();
			Vector2D<float> speed(0, 0);
			wasps.push_back(new Wasp(this, pos, lifeTime, speed));
		}
	}
	for (int i = 0;i < vehicles.size();i++) vehicles[i]->update();
	for (int i = 0;i < logs.size();i++) logs[i]->update();
	for (int i = 0; i < homeFrogs.size(); i++) homeFrogs[i]->update();
	for (int i = 0; i < wasps.size(); i++) wasps[i]->update();
	frog->update();
	// TODO
}

void
Game::run()
{
	while (!exit) {
		// TODO: implementar bucle del juego
		if (frog->GetHomesReached() == 1)
		{
			cout << "Has alcanzado todos los nidos" << endl;
			exit = true;
		}
		else if (frog->GetLives() == 0)
		{
			cout << "Te has quedado sin vidas (0/3)" << endl;
			exit = true;
		}
		handleEvents();
		update();
		render();
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
	while (i < wasps.size() && collision.type == NONE) {
		collision = wasps[i]->checkCollision(rect);
		i++;
	}
	i = 0;
	while (i < vehicles.size() && collision.type == NONE) {
		collision = vehicles[i]->checkCollision(rect);
		i++;
	}
	i = 0;
	while (i < logs.size() && collision.type == NONE) {
		collision = logs[i]->checkCollision(rect);
		i++;
	}
	i = 0;
	while (i < homeFrogs.size() && collision.type == NONE) {
		collision = homeFrogs[i]->checkCollision(rect);
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
			 else inputMap.ignore('#', '\n');
		 }
		 
		 inputMap.close();
	 }

	 for (int i = 0; i < NUMBER_HFROGS; i++)
	 {
		 HomeFrog* homeFrog = new HomeFrog(this, homeFrogsPos[i], frog);
		 homeFrogs.push_back(homeFrog);
	 }
}

int 
Game::getRandomRange(int min, int max) {
	static std::random_device rd;
	static std::mt19937 randomGenerator(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(randomGenerator);
}

