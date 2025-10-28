#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include <random>
#include "vector2D.h"

// Declaraciones anticipadas
class Texture;
class Vehicle;
class Log;
class Frog;
class HomeFrog;
class Wasp;

/**
 * Clase principal del juego.
 */
class Game
{
public:
	// Se actualiza el juego cada tantos milisegundos
	static constexpr int FRAME_RATE = 30;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;
	// Extremo inferior del río
	static constexpr int RIVER_LOW = 210;
	// Numero de HomeFrogs
	static constexpr int NUMBER_HFROGS = 5;
	// Pos Y dE HomeFrogs
	static constexpr float POS_Y_HOMEFROG = 19;
	// Pos x del primer HomeFrogs
	static constexpr float POS_X_HOMEFROG = 13;
	// Separacion HomeFrogs
	static constexpr float SEPARATION_HOMEFROG = 96;
	// Fin juego fuera pantalla izquierda
	static constexpr float GAME_END_LEFT = -150.0f;
	// Fin juego fuera pantalla derecha
	static constexpr float GAME_END_RIGHT = 598.0f;

	// Inicio juego fuera pantalla derecha
	static constexpr float GAME_START_LEFT = 0.0f;
	// Inicio juego fuera pantalla derecha
	static constexpr float GAME_START_RIGHT = 448.0f;

	// Fin pantalla x
	static constexpr float GAME_SCREENEND_X = 420.0f;
	// Fin pantalla x
	static constexpr float GAME_SCREENEND_Y = 402.0f;
	// Pos Rana Inicio
	static constexpr float FROG_INICIO = 205.0f;
	// Pasos Rana
	static constexpr float FROG_STEP = 32.0f;

	// FROG -- (colision offset)
	static constexpr int COLLISION_OFFSET_FROG = 3;
	static constexpr int COLLISION_OFFSET_SCREEN = 9;
	// Tick
	static constexpr int TICK = 1000;

	// WASP -- (tiempo en milisegundos)
	// Avispas tiempo de vida max 
	static constexpr float MAX_WASP_LIFE = 7000.0f;
	// Avispas tiempo de vida max
	static constexpr float MIN_WASP_LIFE = 5000.0f;
	// Avispas tiempo de generacion max
	static constexpr float MIN_WASP_GENERATOR = 7500.0f;
	// Avispas tiempo de generacion min
	static constexpr float MAX_WASP_GENERATOR = 9500.0f;
	// WASP -- (wasp offset)
	static constexpr int WASP_OFFSET_X = 8;
	static constexpr int WASP_OFFSET_Y = 4;


	enum TextureName
	{
		FROG = 0,
		BACKGROUND,
		CAR1,
		CAR2,
		CAR3,
		CAR4,
		CAR5,
		LOG1,
		LOG2,
		WASP,
		NUM_TEXTURES
	};
	enum Type
	{
		NONE, ENEMY, PLATFORM, HOME
	};

	struct Collision
	{
		Type type;
		Vector2D<float> speed;
	};
	

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;

	void render() const;
	void update();
	void handleEvents();

	bool exit;
	float nextWasp;
	Uint32 waspSpawn;

	// Elemento del juego
	// TODO: añadir atributos para los objetos del juego

	std::vector<Vehicle*> vehicles;
	std::vector<Log*> logs;
	std::vector<HomeFrog*> homeFrogs;
	std::vector<Wasp*> wasps;

	std::vector<Point2D<float>> homeFrogsPos = {Point2D<float>(POS_X_HOMEFROG,POS_Y_HOMEFROG),
												Point2D<float>(POS_X_HOMEFROG+SEPARATION_HOMEFROG * 1,POS_Y_HOMEFROG),
												Point2D<float>(POS_X_HOMEFROG + SEPARATION_HOMEFROG * 2,POS_Y_HOMEFROG),
												Point2D<float>(POS_X_HOMEFROG + SEPARATION_HOMEFROG * 3,POS_Y_HOMEFROG),
												Point2D<float>(POS_X_HOMEFROG + SEPARATION_HOMEFROG * 4,POS_Y_HOMEFROG), };
	Frog* frog;

public:
	Game();
	~Game();
	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();

	// Comprueba si hay algún objeto colocado en ese rectángulo
	Collision checkCollision(const SDL_FRect& rect) const;

	void AuxVehicles();
	void loadGame();
	int getRandomRange(int, int);

};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
