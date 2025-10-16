#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include "vector2D.h"
//#include "vehicle.h"

// Declaraciones anticipadas
class Texture;
class Vehicle;

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

	enum TextureName
	{
		FROG = 0,
		BACKGROUND,
		CAR1,
		CAR2,
		CAR3,
		CAR4,
		CAR5,
		NUM_TEXTURES
	};
	enum Type
	{
		NONE, ENEMY, PLATFORM
	};

	struct Collision
	{
		Type type;
		Vector2D<int> speed;
	};
	

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;

	void render() const;
	void update();
	void handleEvents();

	bool exit;

	// Elemento del juego
	// TODO: añadir atributos para los objetos del juego

	std::vector<Vehicle*> vehicles;

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
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
