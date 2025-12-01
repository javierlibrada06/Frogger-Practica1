#include "GameState.h"
#include "SDLApplication.h"
#include "SceneObject.h"

#include <list>
#include <string>
#pragma once
class PauseState : public GameState
{
	std::list<SceneObject*> sceneObjects;
public:
	PauseState(SDLApplication*, std::string, std::list<SceneObject*>);
	~PauseState();
	void update() override;
	void render() const override;
};
