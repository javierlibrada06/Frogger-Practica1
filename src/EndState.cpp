#include "EndState.h"
#include "vector2D.h"
#include "Label.h"
#include "Button.h"
#include "MainMenuState.h"

EndState::EndState(SDLApplication* g, bool win)
	: GameState(g)
{
	if (win) { 
		Label* l = new Label(this, Point2D<float>(LABEL_POSX, LABEL_POSY - LABEL_SEPARATION), SDLApplication::WIN);
		l->setColor(0, COLOR_VALUE, 0);
		gameObjects.push_back(l);
	}
	else {
		Label* l = new Label(this, Point2D<float>(LABEL_POSX, LABEL_POSY - LABEL_SEPARATION), SDLApplication::LOSE);
		l->setColor(COLOR_VALUE, 0, 0);
		gameObjects.push_back(l);
	}
	
	Button* b = new Button(this, Point2D<float>(LABEL_POSX, LABEL_POSY), SDLApplication::INICIO,
		[this]() { game->replaceState(new MainMenuState(game)); });


	addEventListener(b);
	gameObjects.push_back(b);

	Button* e = new Button(this, Point2D<float>(LABEL_POSX, LABEL_POSY + LABEL_SEPARATION), SDLApplication::SALIR,
		[this]() { game->exitGame(); });

	addEventListener(e);
	gameObjects.push_back(e);
}
