#pragma once
#include <SDL3/SDL.h>
#include <array>
#include "Texture.h"
#include "GameState.h"
#include "gameStateMachine.h"

class SDLApplication : public GameStateMachine {
    
	// Se actualiza el juego cada tantos milisegundos
	static constexpr int FRAME_RATE = 30;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;

	// Tick
	static constexpr int TICK = 1000;

	SDL_Window* window;
    SDL_Renderer* renderer;
    bool exit;

    GameState* currentState;

public:
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
		TURTLE,
		NUM_TEXTURES
	};

    SDLApplication();
    ~SDLApplication();
	Texture* getTexture(TextureName name) const;


    void run();
	void render() const;
	void handleEvents();
	void addState(GameState* state);

//private: 
	std::array<Texture*, NUM_TEXTURES> textures;

};

inline Texture*
SDLApplication::getTexture(TextureName name) const
{
	return textures[name];
}
