#include "GameState.h"
#include "Label.h"
#include <filesystem>
#include <utility>
#include <list>
#include <string>
#include "SDLApplication.h"
#pragma once

class Button;
class MainMenuState : public GameState
{

	std::vector<std::pair<Button*, std::string>> maps;

	Button* leftArrow;    // botón flecha izquierda
	Button* rightArrow;   // botón flecha derecha
	Button* selectedButton; // botón actualmente seleccionado
	int selectedIndex = 0;  // índice en maps del botón seleccionado
	using anchor =std::list<std::pair<Button*, std::string>>::iterator;
	anchor it;

	public:	

	MainMenuState(SDLApplication*);
	~MainMenuState();

	void update() override;
	void render() const override;
	void selectNextButton();
	void selectPreviousButton();
	void LoadMaps();
};
