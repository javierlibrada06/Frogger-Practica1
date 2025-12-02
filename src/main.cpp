//
// TecnologÃ­a de la ProgramaciÃ³n de Videojuegos 1
// Facultad de InformÃ¡tica UCM
//
// Plantilla de proyecto con SDL
//
#include "GameError.h"
#include "SDLApplication.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include <fstream>
#include <iostream>
using namespace std;


void showError(const char* title, const char* msg) {
	SDL_MessageBoxButtonData buttons[] = {
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK" }
	};
	SDL_MessageBoxData data{
		SDL_MESSAGEBOX_ERROR,
		nullptr,
		title,
		msg,
		SDL_arraysize(buttons),
		buttons,
		nullptr
	};
	SDL_ShowMessageBox(&data, nullptr);
}

int main(int argc, char* argv[])
{
;
	// TODO: manejar excepciones
	try {
		SDLApplication game = SDLApplication();
		game.pushState(new MainMenuState(&game));
		game.run();
	}
	catch (const GameError& e) {
		showError("Error", e.what());
		return 1;
	}
	return 0;
}
