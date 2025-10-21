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

	// Elemento del juego
	// TODO: añadir atributos para los objetos del juego

	std::vector<Vehicle*> vehicles;
	std::vector<Log*> logs;
	std::vector<HomeFrog*> homeFrogs;
	std::vector<Wasp*> wasps;

	std::vector<Point2D<float>> homeFrogsPos = {Point2D<float>(16.0f,19.0f),
												Point2D<float>(112.0f,19.0f),
												Point2D<float>(208.0f,19.0f),
												Point2D<float>(304.0f,19.0f),
												Point2D<float>(400.0f,19.0f), };
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
