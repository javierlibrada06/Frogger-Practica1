#include "GameState.h"
#include "SDLApplication.h"
#include "SceneObject.h"
#include "PlayState.h"

#include <list>
#include <string>
#pragma once
class PauseState : public GameState
{
	static constexpr float BUTTON_SEPARATION = 75,
						    BUTTON_POSX = SDLApplication::WINDOW_WIDTH / 2,
							BUTTON_POSY = SDLApplication::WINDOW_HEIGHT / 2,
							BACKGROUND_ALPHA = 130 ;
	std::list<SceneObject*> sceneObjects;
public:
	PauseState(SDLApplication*, std::string, std::list<SceneObject*>);
	~PauseState();
	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override { GameState::handleEvent(event); };
};
