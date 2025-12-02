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
	static constexpr float MAP_BUTTON_POS_Y = 300, MAP_BUTTON_POS_X = SDLApplication::WINDOW_WIDTH / 2, LEFT_ARROW_POS_X = 100, MAP_BUTTON_SEPARATION_Y = 50, TITLE_ACTION_POS_Y = 200;
	// Pos x del primer HomeFrogs
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
	void CreateArrowButtons();
	void CreateMapButtons();

	void handleEvent(const SDL_Event& event) override;
};
