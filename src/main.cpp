//
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Plantilla de proyecto con SDL
//

#include "game.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	Game game = Game();
	game.loadGame();
	game.run();
	// TODO: manejar excepciones

	return 0;
}
